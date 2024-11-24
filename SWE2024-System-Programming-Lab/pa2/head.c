#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void Error_proc(){
    switch(errno){
    case EACCES:
    case EISDIR:
    case ENOENT:
    case ENOTDIR:
    case EPERM:
        perror("head");
        break;
    default:
        fprintf(stderr, "head: Error occurred: %d\n", errno);
    }
}

int main(int argc, char *argv[]){
    int line = 10;
    int f_idx = -1;
    FILE *fp;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] != 'n'){ /* 옵션이 -n이 아닌 경우 */
            errno = EINVAL;
            // fprintf(stderr, "head: invalid option\n");
            goto bad;
        } else if(!strncmp(argv[i], "-n", 2)){
            line = atoi(argv[++i]);
            if(argv[i][0] != '0' && line == 0){ /* 옵션 다음에 오는 것이 숫자가 아닌 경우 */
                errno = EINVAL;
                // fprintf(stderr, "head: invalid number of lines\n");
                goto bad;
            }
        } else if(argv[i][0] != '-' && f_idx == -1){ /* 옵션과 그 숫자가 아닌 경우는 파일 이름 */
            f_idx = i;
        }
    }
    if((fp = fopen(argv[f_idx], "r")) == 0)
        goto bad;
    
    /* 파일의 크기를 구해서 할당 */
    if(fseek(fp, 0, SEEK_END))
        goto bad;
    int buf_size = ftell(fp);
    char *buf = (char *)malloc(buf_size);
    if(fseek(fp, 0, SEEK_SET))
        goto bad;

    int i;
    int line_count = 0;
    fread(buf, buf_size, 1, fp);
    for(i = 0; i < buf_size && line_count < line; i++){
        if(buf[i] == '\n'){
            line_count++;
        }
        printf("%c", buf[i]);
    }
    
    free(buf);
    if(fclose(fp))
        goto bad;
    return 0;

    bad:
    Error_proc();
    exit(errno);
}


