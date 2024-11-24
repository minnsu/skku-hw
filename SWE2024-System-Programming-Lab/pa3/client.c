#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string.h>

typedef struct _query {
    int user;
    int action;
    int seat;
} query;

int input(char *buffer, query *req);

int main(int argc, char *argv[]) {
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    // **************
    int flag = 0;
    FILE *fp = NULL;
    // **************

    if (argc == 3) {
        /* Insert your code for terminal input */
    } else if (argc == 4) {
        /* Insert your code for file input */
        // **************
        flag = 1;
        fp = fopen(argv[3], "r");
        // **************
    } else {
        printf("Follow the input rule below\n");
        printf("==================================================================\n");
        printf("argv[1]: server address, argv[2]: port number\n");
        printf("or\n");
        printf("argv[1]: server address, argv[2]: port number, argv[3]: input file\n");
        printf("==================================================================\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("Connection failed\n");
        exit(1);
    }

    /*
     * Insert your PA3 client code
     *
     * You should handle input query
     *
     * Follow the print format below
     *
     * 1. Log in
     * - On success
     *   printf("Login success\n");
     * - On fail
     *   printf("Login failed\n");
     *
     * 2. Reserve
     * - On success
     *   printf("Seat %d is reserved\n");
     * - On fail
     *   printf("Reservation failed\n");
     *
     * 3. Check reservation
     * - On success
     *   printf("Reservation: %s\n");
     *   or
     *   printf("Reservation: ");
     *   printf("%d, ");
     *   ...
     *   printf("%d\n");
     * - On fail
     *   printf("Reservation check failed\n");
     *
     * 4. Cancel reservation
     * - On success
     *   printf("Seat %d is canceled\n");
     * - On fail
     *   printf("Cancel failed\n");
     *
     * 5. Log out
     * - On success
     *   printf("Logout success\n");
     * - On fail
     *   printf("Logout failed\n");
     *
     */
    int i = 0;
    int received[256];
    for(i = 0; i < 256; i++)
        received[i] = 0;
    int first = 1;
    char buffer[256];

    while(1) {
        query req;
        if(flag) {
            if(fgets(buffer, 256, fp) == NULL){
                req.user = 0;
                req.action = 0;
                req.seat = 0;
            } else {
                if(input(buffer, &req) < 0) {
                    printf("Invalid query\n");
                    continue;
                }
            }
        } else {
            fgets(buffer, 256, stdin);
            if(input(buffer, &req) < 0) {
                printf("Invalid query\n");
                continue;
            }
        }

        write(client_socket, (const void *)&req, sizeof(query));
        i = 0;
        read(client_socket, &received[0], sizeof(received[0]));
        if(req.action == 3) {
            if(received[0] == -1){
                printf("Reservation check failed\n");
                goto jump;
            }
            printf("Reservation:");
            if(received[0] == 1) { // 0번 좌석 reserve
                printf(" %d", 0);
                first = 0;
            }
            i = 1;
            while(i < 256 && read(client_socket, &received[i], sizeof(received[i]))){
                if(received[i] == 1) {
                    if(first){ // reserve된 좌석 첫 출력이면 , 없음
                        printf(" %d", i);
                        first = 0;
                    } else
                        printf(", %d", i);
                    received[i] = 0;
                }
                i++;
            }
            first = 1;
            printf("\n");
        } else {
            // read(client_socket, &received[0], sizeof(int));
            switch(req.action) {
            case 1:
                if(received[0] == -1)
                    printf("Login failed\n");
                else
                    printf("Login success\n");
                break;
            case 2:
                if(received[0] == -1)
                    printf("Reservation failed\n");
                else
                    printf("Seat %d is reserved\n", received[0]);
                break;
            case 4:
                if(received[0] == -1)
                    printf("Cancel failed\n");
                else
                    printf("Seat %d is canceled\n", received[0]);
                break;
            case 5:
                if(received[0] == -1)
                    printf("Logout failed\n");
                else
                    printf("Logout success\n");
                break;
            default: break;
            }
        }
        jump:
        if(req.action == 0 && received[0] == 256)
            break;
        received[0] = 0;
    }

    close(client_socket);

    return 0;
}

int input(char *buffer, query *req) {
    int i = 0;
    int s_c = 0;
    for(i = 0; i < (int) strlen(buffer); i++) {
        if(buffer[i] == ' ')
            s_c++;
    }
    if(s_c != 2 || (i > 2 && buffer[i-1] == '\n' && buffer[i-2] == ' ')){
        goto Invalid;
    }
    char *tmp = strtok(buffer, " ");
    if(tmp)
        req->user = atoi(tmp);
    else
        goto Invalid;

    tmp = strtok(NULL, " ");
    if(tmp)
        req->action = atoi(tmp);
    else
        goto Invalid;

    tmp = strtok(NULL, " ");
    if(tmp)
        req->seat = atoi(tmp);
    else
        goto Invalid;

    // printf("{\n\tuser: %d\n\taction: %d\n\tdata: %d\n};\n", req->user, req->action, req->seat);
    return 0;

    Invalid:
    return -1;
}