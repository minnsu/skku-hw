#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

void Error_proc(){
    switch(errno){
    case EACCES:
    case EISDIR:
    case ENOENT:
    case ENOTDIR:
    case EPERM:
        perror("cp");
        break;
    default:
        fprintf(stderr, "cp: Error occurred: %d\n", errno);
    }
}

int main(int argc, char *argv[]){
    if(argc == 1){
        errno = EINVAL;
        fprintf(stderr, "cp: missing file operand\n");
        exit(errno);
    }
    if(argc == 2){
        errno = EINVAL;
        fprintf(stderr, "cp: missing destination file operand after \'%s\'\n", argv[1]);
        exit(errno);
    }
    
    /* argv를 파일 이름으로 open */
    
    FILE *r_fp;
    if((r_fp = fopen(argv[1], "r")) == NULL)
        goto bad;
    
    char dst[256];
    struct stat buf_dst;
    if(stat(argv[2], &buf_dst) < 0){ /* 두번째 요소가 존재하지 않으면 새로운 이름 */
        strcpy(dst, argv[2]);
    }
    if(S_ISDIR(buf_dst.st_mode)){ /* 존재하고 디렉토리면 dst를 절대경로로 변경 후 argv[1] 이름 그대로 추가해서 사용 */
        realpath(argv[2], dst);
        char *last = strtok(argv[1], "/");
        char *tmp = last;
        while(tmp){
            tmp = strtok(NULL, "/");
            last = tmp ? tmp : last;
        }
        strcat(dst, "/");
        strcat(dst, last);
    }
    
    FILE *w_fp;
    if((w_fp = fopen(dst, "w")) == NULL){
        fclose(r_fp);
        goto bad;
    }

    /* 첫번째 파일 크기만큼 할당 */
    if(fseek(r_fp, 0, SEEK_END))
        goto bad;
    int size = ftell(r_fp);
    char *buf = (char *)malloc(size);
    if(fseek(r_fp, 0, SEEK_SET))
        goto bad;
    
    /* 한 번에 읽고, 두번째 파일에 쓰기 */
    fread(buf, size, 1, r_fp);
    fwrite(buf, size, 1, w_fp);

    if(fclose(r_fp) || fclose(w_fp))
        goto bad;
    return 0;

    bad:
    Error_proc();
    exit(errno);
}