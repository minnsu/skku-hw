#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int loop_of(int i) {
        int key = 10;
        int ret = 1;
        while (1) {
                if (i / key) {
                        key *= 10;
                        ret++;
                } else {
                        break;
                }
        }
        return ret;
}

char *set_num(int i, char *tmp) {
        int loop = loop_of(i);
        int j = 0;
        int key = 1;
        for (int k = 0; k < loop - 1; k++) {
                key *= 10;
        }
        while (loop--) {
                tmp[j++] = '0' + i / key;
                i %= key;
                key /= 10;
        }
        tmp[j++] = ' ';
        tmp[j++] = '|';
        tmp[j++] = ' ';
        tmp[j] = '\0';
        return tmp;
}

int main(int argc, char *argv[]) {

        int fd_origin, fd_new;
        fd_origin = open(argv[1], O_RDWR);
        fd_new = open("Aladdin_num.txt", O_RDWR | O_CREAT, 0764);

        char buf[1024];
        int line_num = 1;
        char tmp[9];
        int flag = 1;
        int length;

        set_num(line_num++, tmp);
        write(fd_new, &tmp, 4);
        while ((length = read(fd_origin, buf, 1024)) > 0) {
                for (int i = 0; i < length; i++) {
                        write(fd_new, &buf[i], 1);
                        if (buf[i] == '\n') {
                                set_num(line_num, tmp);
                                write(fd_new, &tmp, loop_of(line_num) + 3);
                                line_num++;
                        }
                }
        }

        close(fd_origin);
        close(fd_new);
        return 0;
}