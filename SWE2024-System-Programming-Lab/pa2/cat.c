#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

void Error_proc(){
    switch(errno){
    case EACCES:
    case EISDIR:
    case ENOENT:
    case ENOTDIR:
    case EPERM:
        perror("cat");
        break;
    default:
        fprintf(stderr, "cat: Error occurred: %d\n", errno);
    }
}

int main(int argc, char *argv[]){
    struct stat buf_src;
    if(stat(argv[1], &buf_src) < 0)
        goto bad;
    if(S_ISDIR(buf_src.st_mode)){
        errno = EISDIR;
        goto bad;
    }
    
    FILE *fp;
    if((fp = fopen(argv[1], "r")) == 0)
        goto bad;
    
    /* 파일 크기만큼 할당 */
    if(fseek(fp, 0, SEEK_END))
        goto bad;
    int buf_size = ftell(fp);
    char *buf = (char *)malloc(buf_size);
    if(fseek(fp, 0, SEEK_SET))
        goto bad;
    
    /* 전부 읽고 출력 */
    fread(buf, buf_size, 1, fp);
    printf("%s", buf);
    
    free(buf);
    if(fclose(fp))
        goto bad;
    return 0;

    bad:
    Error_proc();
    exit(errno);
}