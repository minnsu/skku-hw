#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void Error_proc(){
    switch(errno){
    case EACCES:
    case EISDIR:
    case ENOENT:
    case ENOTDIR:
    case EPERM:
        perror("pwd");
        break;
    default:
        fprintf(stderr, "pwd: Error occurred: %d\n", errno);
    }
}

int main(int argc, char *argv[]){
    char path[256];
    if(getcwd(path, 256) == NULL)
        goto bad;
    printf("%s\n", path);
    return 0;
    bad:
    Error_proc();
    exit(errno);
}