#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define T_MSG 20

typedef struct {
    long msgtype;
    int sender;
    char text[512];
} msgbuf;

typedef struct {
    long msgtype;
    char timestamp[512];
} msgbuf_ack;

int main() {
    key_t key = ftok(".", 'a');
    int user_id, receiver_id, qid, pid;
    printf("My id is: ");
    scanf("%d", &user_id);
    getchar();
    printf("Enter the receiver of your message: ");
    scanf("%d", &receiver_id);
    getchar();
    /* create message queue */
    if ((qid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget failed\n");
        exit(1);
    }
    if ((pid = fork()) == 0) {
        while (1) {
            /* 
	     * child receives messages
	     * 1. receive normal message
             * 1-1. print "RECEIVED [normal message]"
             * 1-2. send ack message (current timestamp)
             * 2. receive ack message using read_time and IPC_NOWAIT
             * 2-1. print "[receiver_id] read message at:\t[timestamp]"
	     */
            msgbuf buf;
            msgbuf_ack read_time;
            if (msgrcv(qid, (void *)&buf, sizeof buf, user_id, IPC_NOWAIT) > 0) {
                msgbuf_ack ack;
                ack.msgtype = T_MSG + receiver_id;
                /* your code */
                printf("RECEIVED %s\n", buf.text);
                time_t tmp = time(NULL);
                strcpy(ack.timestamp, ctime(&tmp));
                msgsnd(qid, (void *)&ack, sizeof ack, IPC_NOWAIT);
            }
            /* your code */
            if(msgrcv(qid, (void *)&read_time, sizeof read_time, T_MSG + user_id, IPC_NOWAIT) > 0){
                printf("%d read message at:\t%s\n", receiver_id, read_time.timestamp);
            }
        }

    } else {
        while (1) {
            /* 
	     * parent sends messages
             * 1. get normal message from stdin
             * 2. if "quit", exit both parent and child (use SIGINT)
             * 3. send normal message
	     */
            msgbuf buf;
            buf.msgtype = receiver_id;
            char *line = NULL;
            size_t len = 0;
            getline(&line, &len, stdin);
            /* your code */
            if(strncmp(line, "quit", 4) == 0){
                end:
                kill(pid, SIGINT);
                wait(NULL);
                free(line);
                break;
            }
            strcpy(buf.text, line);
            buf.sender = user_id;
            if(msgsnd(qid, (void *)&buf, sizeof buf, IPC_NOWAIT) == -1){
                perror("msgsnd error");
                goto end;
            }
            free(line);
        }
    }
}
