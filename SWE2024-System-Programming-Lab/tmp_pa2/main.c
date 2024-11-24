#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>

#define MAX_ARGC 256
#define CMD_LENGTH 256
#define PATH_LENGTH 256

char binary_path[PATH_LENGTH];

// Append appropriate path to cmd. You can use new_cmd.
int append_path(const char *cmd, char *new_cmd){
    if(!strcmp(cmd, "ls") || !strcmp(cmd, "grep"))
        sprintf(new_cmd, "/bin/%s", cmd);
    else if(!strcmp(cmd, "man") || !strcmp(cmd, "sort") || !strcmp(cmd, "awk") || !strcmp(cmd, "bc"))
        sprintf(new_cmd, "/usr/bin/%s", cmd);
    else if(!strcmp(cmd, "head") || !strcmp(cmd, "tail") || !strcmp(cmd, "cat") || !strcmp(cmd, "cp") || !strcmp(cmd, "mv") || !strcmp(cmd, "rm") || !strcmp(cmd, "pwd"))
        sprintf(new_cmd, "%s/%s", binary_path ,cmd);
    else
        realpath(cmd, new_cmd);
}

// Return 1 if "cmds" is invalid. "cmds" is only executable binary name (./a.out, ls, grep, ... etc. )
int check_valid(const char *cmds){
    if(cmds[0] == '.'){ // if cmds starts with '.'. Check that file is currently exist.
        struct stat buf;
        if(stat(cmds, &buf) == 0)
            return 1;
        else {
            fprintf(stderr, "mini: command not found\n");
            exit(errno);
        }
    }
    if(strcmp(cmds, "ls") && strcmp(cmds, "man") && strcmp(cmds, "grep") 
        && strcmp(cmds, "sort") && strcmp(cmds, "awk") && strcmp(cmds, "bc")
        && strcmp(cmds, "head") && strcmp(cmds, "tail") && strcmp(cmds, "cat")
        && strcmp(cmds, "cp") && strcmp(cmds, "mv") && strcmp(cmds, "rm") && strcmp(cmds, "pwd")){
        fprintf(stderr, "mini: command not found\n");
        exit(errno);
    }
    return 1;
}

// Check the number of "target" character in string.
int charInStr(const char *string, char target){
    int ret = 0;
    size_t len = strlen(string);
    for(int i = 0; i < len; i++){
        if(string[i] == target)
            ret++;
    }
    return ret;
}

// Split cmds to argument vector. "cmds" is not maintained. Allocation of "argv" is caller's responsibillity
void splitcmds(char *cmds, char *argv[]){
    int argc = charInStr(cmds, ' ') + 1;
    
    int idx = 0;
    char *ptr = strtok(cmds, " ");
    while(ptr){
        argv[idx++] = ptr;
        ptr = strtok(NULL, " ");
    }
    argv[idx] = 0;
}

// Divide cmds by the first pipeline '|'. "cmds" is maintained. Allocation of "left", "right" is caller's responsibillity
void parsepipe(const char *cmds, char *left, char *right){
    size_t len = strlen(cmds);
    int i, lidx = 0, ridx = 0;
    int isLeft = 1;
    int find = 0;
    for(i = 0; i < len; i++){
        if(cmds[i] == '|' && !find){
            find = 1;
            isLeft = 0;
            i++;
            continue;
        }

        if(isLeft)
            left[lidx++] = cmds[i];
        else
            right[ridx++] = cmds[i];
    }
    left[lidx] = 0;
    right[ridx] = 0;
}

// Execute "cmds" that have redirection characters '<', '>', and ">>". "cmds" is not maintained.
void redirect(char *cmds){
    int i_fd, o_fd;
    
    char *argv[MAX_ARGC];
    // char copy[PATH_LENGTH];
    // strcpy(copy, cmds);
    splitcmds(cmds, argv);

    int i;
    int end_cmd = MAX_ARGC;
    for(i = 0; i < CMD_LENGTH && argv[i]; i++){
        if(!strcmp(argv[i], "<")){
            end_cmd = i < end_cmd ? i : end_cmd;
            close(0);
            if((i_fd = open(argv[++i], O_RDONLY)) < 0){
                perror("mini");
                exit(errno);
            }
        } else if(!strcmp(argv[i], ">")) {
            end_cmd = i < end_cmd ? i : end_cmd;
            close(1);
            o_fd = open(argv[++i], O_CREAT | O_WRONLY, 438);
        } else if(!strcmp(argv[i], ">>")) {
            end_cmd = i < end_cmd ? i : end_cmd;
            close(1);
            o_fd = open(argv[++i], O_CREAT | O_WRONLY | O_APPEND, 438);
        }
    }
    argv[end_cmd] = 0;

    check_valid(argv[0]);
    char new_cmd[PATH_LENGTH];
    append_path(argv[0], new_cmd);
    
    execv(new_cmd, argv);
    exit(errno);
}

// Run normal, redirect cmd. This should be called in forked process.
void run_default(char *cmds){
    int status;
    int i_red_count = charInStr(cmds, '<');
    int o_red_count = charInStr(cmds, '>');

    char *argv[MAX_ARGC];
    splitcmds(cmds, argv);
    
    if(i_red_count || o_red_count){
        int i_fd, o_fd;
        int end_cmd = MAX_ARGC;
        int write_flag = O_CREAT | O_WRONLY;

        for(int i = 0; i < MAX_ARGC && argv[i]; i++){
            if(!strcmp(argv[i], "<")){
                end_cmd = i < end_cmd ? i : end_cmd;
                close(0);
                if((i_fd = open(argv[++i], O_RDONLY)) < 0){
                    perror("mini: open");
                    exit(errno);
                }
            } else if (argv[i][0] == '>'){
                end_cmd = i < end_cmd ? i : end_cmd;
                write_flag |= (o_red_count == 1 ? 0 : O_APPEND);
                close(1);
                if((o_fd = open(argv[++i], write_flag, 438)) < 0){
                    perror("mini: open");
                    exit(errno);
                }
            }
        }
        argv[end_cmd] = 0;
    }

    check_valid(argv[0]);
    char new_cmd[PATH_LENGTH];
    append_path(argv[0], new_cmd);

    execv(new_cmd, argv);
    exit(errno);
}

// Run pipe cmds.
void run_pipe(char *cmds, int pipecount){
    char left[PATH_LENGTH];
    char right[PATH_LENGTH];
    
    int save_stdin;
    save_stdin = dup(STDIN_FILENO);
    int pgid = 0;
    int pfd[2];

    for(int i = 0; i <= pipecount; i++){
        parsepipe(cmds, left, right);
        if(pipe(pfd) < 0){
            perror("mini: pipe");
            exit(errno);
        }
        int cid_left, cid_right;
        if((cid_left = fork()) == 0){
            if(setpgid(0, pgid) < 0){
                perror("mini: setpgid");
                exit(errno);
            }
            if(!pgid){ /* get foreground permission */
                if(tcsetpgrp(STDIN_FILENO, getpid()) < 0){
                    perror("mini: tcsetpgrp");
                    exit(errno);
                }
            }
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            if(i < pipecount){
                close(1);
                dup(pfd[1]);
                close(pfd[0]);
                close(pfd[1]);
            }
            run_default(left);
            exit(errno);
        }
        if(i == 0)
            pgid = cid_left;
        if(i == pipecount)
            break;
        close(0);
        dup(pfd[0]);
        close(pfd[0]);
        close(pfd[1]);
        strcpy(cmds, right);
    }
    close(0); /* Close the remaining pipe fd */
    dup(save_stdin); /* restore stdin */
    close(save_stdin);
    for(int i = 0; i <= pipecount; i++){
        wait(NULL);
    }
}

// SIGCHLD handler. Kill all processes in generated child's process group.
void sigchld_handler(int sig){
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0){
        if(WIFSTOPPED(status)){ // If child stopped by Ctrl-Z, then kill group processes and itself.
            kill(pid, SIGKILL);
            kill(-pid, SIGKILL);
        }
    }
}

int main(int argc, char *argv[]){
    char *cmds;
    size_t cmds_len;
    char path[PATH_LENGTH];

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
    /* for implemented binary like head, tail, cat, cp, mv, rm, and pwd */
    getcwd(binary_path, PATH_LENGTH);

    int cid, status;
    while(1){
        printf("mini $ ");
        getline(&cmds, &cmds_len, stdin);
        cmds[strlen(cmds) - 1] = 0;

        // builtin cmds : exit, cd
        if(!strncmp(cmds, "exit", 4) && (cmds[4] == '\0' || cmds[4] == '\n' || cmds[4] == ' ')){
            char *exit_num = strtok(cmds, " ");
            exit_num = strtok(NULL, " ");
            int num = exit_num == NULL ? 0 : atoi(exit_num);
            fprintf(stderr, "exit");
            exit(num);
        }
        if(!strncmp(cmds, "cd", 2) && (cmds[2] == '\0' || cmds[2] == '\n' || cmds[2] == ' ')){
            if(strlen(cmds) < 4){
                fprintf(stderr, "No directory specified.\n"); // 임의로 넣은 것.
                continue;
            }
            strcpy(path, strtok(cmds, " "));
            strcpy(path, strtok(NULL, " "));
            if(chdir(path) < 0)
                perror("cd");
            continue;
        }
        
        int pipecount = 0;
        pipecount = charInStr(cmds, '|');
        
        signal(SIGTTOU, SIG_IGN);
        if(pipecount){
            run_pipe(cmds, pipecount);
        } else { // normal, redirect cmd
            if((cid = fork()) == 0){
                if(setpgid(0, 0) < 0){
                    perror("mini: setpgid");
                    exit(errno);
                }
                if(tcsetpgrp(STDIN_FILENO, getpid()) < 0){ /* get foreground permission */
                    perror("mini: tcsetpgrp");
                    exit(errno);
                }
                signal(SIGINT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                run_default(cmds);
                exit(0);
            }
            wait(NULL);
        }
        if(tcsetpgrp(STDIN_FILENO, getpid()) < 0){ /* retreive foreground permission */
            perror("mini: tcsetpgrp mainloop");
            exit(errno);
        }
        signal(SIGTTOU, SIG_DFL);
    }
    return 0;
}