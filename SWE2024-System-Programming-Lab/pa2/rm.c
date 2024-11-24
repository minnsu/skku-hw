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
        perror("rm");
        break;
    default:
        fprintf(stderr, "rm: Error occurred: %d\n", errno);
    }
}

int main(int argc, char *argv[]){
    if(argc == 1){
        // fprintf(stderr, "rm: missing operand\n");
        errno = EINVAL;
        goto bad;
    }
    if(unlink(argv[1]) < 0)
        goto bad;
    return 0;
    
    bad:
    Error_proc();
    exit(errno);
}