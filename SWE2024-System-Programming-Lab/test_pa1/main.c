#include "minsu.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void type1(int fd, char *str);
void type2(int fd, char *str);
void type3(int fd, char *str);
void type4(int fd, char *str); /* word_v_size = 2 */

int main(int argc, char *argv[]) {
    char str[513];

    int fd;
    int type;
    while (1) {
        read_line(str);
        if (isEqualWord("PA1EXIT", str))
            break;
        fd = open(argv[1], O_RDONLY);
        type = check_type(str);
        switch (type) {
        case 1:
            type1(fd, str);
            break;
        case 2:
            type2(fd, str);
            break;
        case 3:
            type3(fd, str);
            break;
        case 4:
            type4(fd, str);
            break;
        }
        print_str("\n");
        close(fd);
    }
    return 0;
}

void type1(int fd, char *str) {
    char *line = (char *)malloc(1024);
    int line_num = 1;
    int first = 1;
    int EOFflag = 1;
    while (EOFflag) {
        if(read_fline(fd, line) == 0)
            EOFflag = 0;
        search_type1(line, str, line_num, &first);
        line_num++;
    }
}

void type2(int fd, char *str) {
    char *line = (char *)malloc(1024);
    char **word_v;
    int word_v_size;
    /* make word vector */
    int delim_count = 0;
    for (int i = 0; i < str_length(str); i++) {
        if (str[i] == ' ')
            delim_count++;
    }
    word_v_size = delim_count + 1;
    word_v = (char **)malloc(sizeof(char *) * (delim_count + 1));
    parse(str, word_v, ' ');

    int line_num = 1;
    int find_count = 0;
    int first = 1;
    int EOFflag = 1;
    while (EOFflag) {
        if(read_fline(fd, line) == 0)
            EOFflag = 0;
        // find_count = search_type2(line, word_v, word_v_size);
        if (search_type2(line, word_v, word_v_size)) {//find_count >= word_v_size) {
            if(!first)
                print_str(" ");
            print_int(line_num);
            first = 0;
        }
        find_count = 0;
        line_num++;
    }
}
void type3(int fd, char *str) {
    char *line = (char *)malloc(1024);
    int line_num = 1;
    /* delete quote */
    int str_size = str_length(str);
    for (int i = 0; i < str_size - 1; i++) {
        str[i] = str[i + 1];
    }
    str[str_size - 2] = '\0';

    int first = 1;
    int EOFflag = 1;
    while (EOFflag) {
        if(read_fline(fd, line) == 0)
            EOFflag = 0;
        search_type3(line, str, line_num, &first);
        line_num++;
    }
}

void type4(int fd, char *str) { 
    char *line = (char *)malloc(1024);
    char **word_v;
    int word_v_size;
    word_v = (char **)malloc(sizeof(char *) * 2);
    parse(str, word_v, '*');

    int line_num = 1;
    int flag = 0;
    int first = 1;
    int EOFflag = 1;
    while (EOFflag) {
        if(read_fline(fd, line) == 0)
            EOFflag = 0;
        flag = search_type4(line, word_v);
        if (flag) {
            if(!first)
                print_str(" ");
            print_int(line_num);
            first = 0;
        }
        flag = 0;
        line_num++;
    }
}