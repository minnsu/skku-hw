#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void Error_proc(){
    switch(errno){
    case EACCES:
    case EISDIR:
    case ENOENT:
    case ENOTDIR:
    case EPERM:
        perror("mv");
        break;
    default:
        fprintf(stderr, "mv: Error occurred: %d\n", errno);
    }
}

char *extract_file_name(const char *path){ /* 첫번째 argument로부터 마지막 file 이름만 추출 */
    char tmp[256];
    strcpy(tmp, path);

    char *ttmp;    
    char *name = strtok(tmp, "/");
    while(ttmp){
        ttmp = strtok(NULL, "/");
        if(ttmp)
            name = ttmp;
    }
    return name;
}

int main(int argc, char *argv[]){
    if(argc == 1){
        fprintf(stderr, "mv: missing file operand\n");
        errno = EINVAL;
        exit(errno);
    }
    if(argc == 2){
        fprintf(stderr, "mv: missing destination file operand after \'%s\'\n", argv[1]);
        errno = EINVAL;
        exit(errno);
    }

    char src_path[256], dst_path[256];

    /* argv[1] 미존재 -> 오류 */
    struct stat buf_src;
    if(stat(argv[1], &buf_src) < 0)
        goto bad;
    realpath(argv[1], src_path);

    /* argv[2] 존재 -> realpath */
    struct stat buf_dst;
    if(stat(argv[2], &buf_dst) == 0){
        realpath(argv[2], dst_path);
        if(S_ISDIR(buf_dst.st_mode)){
            /* 마지막 요소 추출 후 dst_path에 추가 */
            char *last = strtok(argv[1], "/");
            char *tmp = last;
            while(tmp){
                tmp = strtok(NULL, "/");
                last = tmp ? tmp : last;
            }
            strcat(dst_path, "/");
            strcat(dst_path, last);
        }
    } else {
        /* 존재하지 않으면 입력 받은 것이 이름 */
        strcpy(dst_path, argv[2]);
    }

    if(rename(src_path, dst_path) < 0)
        goto bad;
    return 0;
    bad:
    Error_proc();
    exit(errno);
}