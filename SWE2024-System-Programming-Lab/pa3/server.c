#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <stdio.h>

typedef struct _query {
    int user;
    int action;
    int data;
} query;

struct user_t {
    int registered;
    int login;
    int password;
} user[1024];
pthread_mutex_t user_lock;

struct seat_t {
    pthread_mutex_t lock;
    int owner;
} seat[256];

void *thread(void *arg) {
    int connfd = *((int *)arg);
    pthread_detach(pthread_self());
    free(arg);
    int n;
    query req;
    int ret = 0;
    int current_uid = -1;
    int res_count = 0;

    while((n = read(connfd, &req, sizeof(query))) > 0) {
        // printf("query {\n\tuser : %d\n\taction : %d\n\tdata : %d\n}\n", req.user, req.action, req.data);
        if(req.action != 0 && current_uid == -1 && req.action != 1) // login 안되어 있는데 다른 action 요청
            goto fail;
        if(req.action != 0 && current_uid != -1 && current_uid != req.user) // 다른 user id로 request 들어온 경우
            goto fail;

        if(req.user == 0 && req.action == 0 && req.data == 0) { // client requested exit = send {0, 0, 0}
            pthread_mutex_lock(&user_lock);
            user[current_uid].login = 0;
            pthread_mutex_unlock(&user_lock);
            current_uid = -1;
            ret = 256;
            write(connfd, (void *)&ret, sizeof(ret));
            break;
        }

        switch(req.action) {
        case 1:
            if(current_uid != -1 || req.user < 0 || req.user >= 1024)
                goto fail;
            pthread_mutex_lock(&user_lock);
            if(user[req.user].registered == 0) {
                user[req.user].registered = 1;
                user[req.user].password = req.data;
                user[req.user].login = 1;

                current_uid = req.user;
            } else if(user[req.user].login == 0) {
                if(user[req.user].password == req.data) {
                    user[req.user].login = 1;
                    current_uid = req.user;
                }
            }
            pthread_mutex_unlock(&user_lock);
            if(current_uid == -1)
                goto fail;
            else{
                ret = 1;
                write(connfd, (void *)&ret, sizeof(ret));
            }
            break;
        case 2:
            if(req.data < 0 || req.data > 255)
                goto fail;
            int success = 0;
            pthread_mutex_lock(&seat[req.data].lock);
            if(seat[req.data].owner == -1) {
                seat[req.data].owner = current_uid;
                success = 1;
            }
            pthread_mutex_unlock(&seat[req.data].lock);
            if(success == 0)
                goto fail;
            else
                write(connfd, (void *)&req.data, sizeof(req.data));
            break;
        case 3:
            res_count = 0;
            for(int i = 0; i < 256; i++) {
                pthread_mutex_lock(&seat[i].lock);
                if(seat[i].owner == current_uid)
                    res_count++;
                pthread_mutex_unlock(&seat[i].lock);
            }
            if(res_count == 0) {
                goto fail;
            } else {
                for(int i = 0; i < 256; i++){
                    pthread_mutex_lock(&seat[i].lock);
                    ret = seat[i].owner == current_uid ? 1 : 0;
                    write(connfd, (void *)&ret, sizeof(ret));
                    pthread_mutex_unlock(&seat[i].lock);
                }
            }

            break;
        case 4:
            if(req.data < 0 || req.data > 255)
                goto fail;
            res_count = 0;
            for(int i = 0; i < 256; i++) {
                pthread_mutex_lock(&seat[i].lock);
                if(seat[i].owner == current_uid)
                    res_count++;
                pthread_mutex_unlock(&seat[i].lock);
            }
            pthread_mutex_lock(&seat[req.data].lock);
            if(res_count == 0 || seat[req.data].owner != current_uid) {
                pthread_mutex_unlock(&seat[req.data].lock);
                goto fail;
            } else
                seat[req.data].owner = -1;
            pthread_mutex_unlock(&seat[req.data].lock);
            write(connfd, (void *)&req.data, sizeof(req.data));
            break;
        case 5:
            if(req.user != current_uid)
                goto fail;
            else {
                pthread_mutex_lock(&user_lock);
                user[current_uid].login = 0;
                pthread_mutex_unlock(&user_lock);
                current_uid = -1;
                ret = 1;
                write(connfd, (void *)&ret, sizeof(ret));
            }
            break;
        default:
            goto fail;
            break;
        }
        continue;

        fail:
        ret = -1;
        write(connfd, (void *)&ret, sizeof(ret));
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    if(bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	    return 0;

    if(listen(serverSocket, 1024) < 0)
	    return 0;

    /*
     * Insert your PA3 server code
     *
     * You should generate thread when new client accept occurs
     * and process query of client until get termination query
     *
     */

    for(int j = 0; j < 256; j++){
        seat[j].owner = -1;
        pthread_mutex_init(&seat[j].lock, (pthread_mutexattr_t *)NULL);
    }
    
    pthread_t tid[2048];
    int i = 0;
    int *connfdp;
    int connecting_address_length = sizeof(serverAddr);
    while(1) {
        connfdp = (int *)malloc(sizeof(int));
        if((*connfdp = accept(serverSocket, (struct sockaddr *)&serverAddr, (socklen_t *)&connecting_address_length)) < 0){
            free(connfdp);
            continue;
        }
        pthread_create(&tid[i++], NULL, thread, connfdp);
    }
    return 0;
}
