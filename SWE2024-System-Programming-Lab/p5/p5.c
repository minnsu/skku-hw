#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char *cmd = NULL;
    size_t size = 0;
    char path[100];

    while (1) {
        printf("$ ");
        /* get input */
        if ((getline(&cmd, &size, stdin)) < 0) {
            perror("getline failed\n");
            exit(1);
        }

        /* if "quit", exit */
        if (strncmp(cmd, "quit", 4) == 0) {
            free(cmd);
            exit(0);
        }

        /* separate command name and options */
        /* ---------your code here---------- */
        char *argv[128];
        int k = 0;
        char *tmp= strtok(cmd, " ");
        while(tmp != NULL){
            argv[k] = (char*)malloc(strlen(tmp));
            argv[k] = tmp;
            k++;
            tmp = strtok(NULL, " ");
        }
        argv[k-1][strlen(argv[k-1])-1] = 0;
        argv[k] = NULL;

        /* execute command using fork()
           you only need to use fork() once! */
        /* ---------your code here---------- */

        char path[100];
        sprintf(path, "/bin/%s", argv[0]);
        int pid = fork();
        if(pid == 0){
            execv(path, argv);
            exit(0);
        }
        wait(NULL);
    }
}