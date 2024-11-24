#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int num_send_sig;
int num_recv_sig = 0;
int num_recv_ack = 0;
pid_t pid;
/* DO NOT MODIFY OR ADD CODE ABOVE */

void recv_ack_handler(int sig) {
    num_recv_ack++;
    return;
}

void terminate_handler(int sig) {
    printf("receiver: total received signal(s): %d\n", num_recv_sig);
    exit(0);
}

void sending_handler(int sig) {
    /* your code here */
    if(num_send_sig - num_recv_ack){
        printf("sender: total remaining signal(s): %d\n", num_send_sig - num_recv_ack);
        kill(pid, SIGUSR1);
    } else{
        printf("all signals have been sent\n");
        kill(pid, SIGINT);
        exit(0);
    }
    alarm(1);
    return;
}

void sending_ack(int sig) {
    /* your code here */
    num_recv_sig++;
    printf("receiver: received #%d signal and sending ack\n", num_recv_sig);
    kill(pid, SIGUSR1);
    return;
}

int main(int argc, char *argv[]) {
    /* DO NOT MODIFY MAIN */

    num_send_sig = atoi(argv[1]);
    printf("total number of signal(s): %d\n", num_send_sig);

    if ((pid = fork()) == 0) {
        pid = getppid();
        /* In the child process pid, == parent's pid,
           [sending_ack] function is installed as signal [SIGUSR1]'s handler
           [terminate_handler] function is installed as signal [SIGINT]'s handler */
        signal(SIGUSR1, sending_ack);
        signal(SIGINT, terminate_handler);
        while (1)
            ;
    } else {
        /* In the parent process, pid == child's pid,
           [recv_ack_handler] function is installed as signal [SIGUSR1]'s handler
           [sending_handler] function is installed as signal [SIGINT]'s handler */
        signal(SIGUSR1, recv_ack_handler);
        signal(SIGALRM, sending_handler);
        alarm(1);
        while (1)
            ;
    }
    return 0;
}
/* How the program works--------------------------------------------------------------------------------|
 1. SIGALARM signal is sent from parent process when alarm(1) is called.                                |
 2. sending_handler function is called                                                                  |
 3. sending_handler function should send SIGUSR1s to child while there are remaining signals to be sent |
   3-1. sending_handler should send SIGINT when all signals are sent                                    |
   3-2. sending_handler calls alarm(1) and repeats from 2                                               |
 4. sending_ack function is called from child process                                                   |
 5. sending_ack function should send SIGUSR1 to parent and recv_ack_handler is called from parent       |
 6. When all signals are sent and received, SIGINT from 3-1 calls terminate_handler                     |
 7. done                                                                                                |
-------------------------------------------------------------------------------------------------------*/
