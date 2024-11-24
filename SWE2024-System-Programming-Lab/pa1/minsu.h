#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int check_type(char *str) {
    int c = 0;
    while (str[c]) {
        if (str[c] == '"')
            return 3;
        else if (str[c] == ' ')
            return 2;
        else if (str[c] == '*')
            return 4;
        c++;
    }
    return 1;
}

int read_line(char *str) {
    int c = read(0, str, 512);
    str[c - 1] = '\0';
    return c;
}

int read_fline(int fd, char *str) { /* eof 탐지? \n이면 1 반환? */
    char *tmp = str;
    int flag = 0;
    while (flag = read(fd, tmp, 1)) {
        if (tmp[0] == '\n') {
            break;
        }
        tmp++;
    }
    // tmp == 0;
    tmp[0] = '\0';
    return flag;
}

int str_length(char *str) {
    int c = 0;
    while (str[c++]) {
    }
    return c - 1;
}

int print_str(char *str) { return write(1, str, str_length(str)); }

/* under 200 million */
void print_int(int num) {
    int key = 10;
    int loop = 1;
    while (num / key) {
        key *= 10;
        loop++;
    }
    key /= 10;
    char *tmp_str = (char *)malloc(loop + 1);
    int i;
    for (i = 0; i < loop; i++) {
        tmp_str[i] = '0' + num / key;
        num %= key;
        key /= 10;
    }
    tmp_str[i] = '\0';
    print_str(tmp_str);
    free(tmp_str);
}

void str_ncpy(char *dst, char *src, int size) {
    int i;
    for (i = 0; i < size; i++)
        dst[i] = src[i];
    dst[i] = '\0';
}

void parse(char *str, char **word_v, char delim) {
    int c = 0, s = 0;
    int v_idx = 0;
    while (str[c]) {
        if (str[c] == delim || str[c] == '\n' || str[c] == '\0') {
            word_v[v_idx] = (char *)malloc(c - s + 1);
            str_ncpy(word_v[v_idx], str + s, c - s);
            s = c + 1;
            v_idx++;
        }
        c++;
    }
    word_v[v_idx] = (char *)malloc(c - s + 1);
    str_ncpy(word_v[v_idx], str + s, c - s);
}

int charcmp(char ref, char tar) {
    if ((('a' <= tar && tar <= 'z') || ('A' <= tar && tar <= 'Z'))
        && (('a' <= ref && ref <= 'z') || ('A' <= ref && ref <= 'Z'))) {
        if (tar == ref)
            return 1;
        else if (tar - 'a' + 'A' == ref)
            return 1;
        else if (tar - 'A' + 'a' == ref)
            return 1;
        return 0;
    }
    if(ref == tar)
        return 1;
    return 0;
}

int isEqualWord(char *word1, char *word2) {
    int size1 = str_length(word1);
    if (size1 != str_length(word2))
        return 0;
    int i;
    for (i = 0; i < size1; i++) {
        // if (word1[i] != word2[i])
        if(!charcmp(word1[i], word2[i]))
            return 0;
    }
    return 1;
}

/* writing symbol? 1641:4 (to Tom)에서 괄호는 not writing symbol? */
int search_type1(char *line, char *word, int line_num, int *first) {
    char *tmp = line;
    int line_size = str_length(line);
    int word_size = str_length(word);
    for (int i = 0; i < line_size; i++) {
        // if (line[i] != word[0])
        if(!charcmp(line[i], word[0]))
            continue;
        // 구문의 시작이 단어 처음인 경우에만 찾는 조건, 예를 들어 활성화되면
        // "is"로 입력한 구문은 문자열에 His가 있어도 찾지 않는다
        if (i != 0 && line[i - 1] != ' ')
            continue;

        int j;
        for (j = 0; j < word_size; j++) {
            // if (line[i + j] != word[j])
            if(!charcmp(line[i+j], word[j]))
                break;
        }
        if (j == word_size &&
            (line[i + j] == ' ' || line[i + j] == '\n' || line[i + j] == '\0') // || line[i+j] == ')')
            // -> 활성화되면 단어가 공백 등 완전히 끝날 때에만 찾는다
            // ex) 활성화되면 nam을 입력했을 때, name을 찾지 않는다.
        ) {
            if(*first == 0)
                print_str(" ");
            print_int(line_num);
            print_str(":");
            print_int(i);
            *first = 0;
        }
    }
}

int search_type2(char *line, char **word_v, int word_v_size) {
    char **line_word_v;
    int delim_count = 0;
    /* line parsing */
    for (int i = 0; i < str_length(line); i++) {
        if (line[i] == ' ')
            delim_count++;
    }
    int line_word_v_size = delim_count + 1;
    line_word_v = (char **)malloc(sizeof(char *) * (delim_count + 1));
    parse(line, line_word_v, ' ');

    /* compare each word, line word : word vector element */
    // 현재 정확히 일치하는 단어, 즉, 공백으로 구분된 단어가 정확히 일치해야
    // find_count 증가, writing symbol이 있다면 세지 않는다
    int find_count = 0;
    int *find_flag = (int *)malloc(sizeof(int) * word_v_size);
    for(int i = 0; i < word_v_size; i++)
        find_flag[i] = 0;
    
    for (int i = 0; i < line_word_v_size; i++) {
        for (int j = 0; j < word_v_size; j++) {
            if (isEqualWord(line_word_v[i], word_v[j]))
                find_flag[j] = 1;
            // find_count++;
        }
    }
    for(int i = 0; i < word_v_size; i++){
        if(!find_flag[i])
            return 0;
    }
    return 1;
}

int search_type3(char *line, char *word, int line_num, int *first) {
    char *tmp = line;
    int line_size = str_length(line);
    int word_size = str_length(word);
    for (int i = 0; i < line_size; i++) {
        // if (line[i] != word[0])
        if(!charcmp(line[i], word[0]))
            continue;
        // 구문의 시작이 단어 처음인 경우에만 찾는 조건,
        // 예를 들어 활성화되면 "is"로 입력한 구문은 문자열에 His가 있어도 찾지 않는다
        if (i != 0 && line[i - 1] != ' ') continue;

        int j;
        for (j = 0; j < word_size; j++) {
            // if (line[i + j] != word[j])
            if(!charcmp(line[i+j], word[j]))
                break;
        }
        if (j == word_size // && (line[i+j] == ' ' || line[i+j] == '\n' || line[i+j] == '\0' || line[i+j] == ')') 
                      // -> 활성화되면 구문 끝단어가 공백 등 완전히
                      // 끝날 때에만 찾음 ex) 활성화되면 "name i"를 구문으로
                      // 입력했을 때, name is를 찾지 못함
        ) {
            if(*first == 0)
                print_str(" ");
            print_int(line_num);
            print_str(":");
            print_int(i);
            *first = 0;
        }
    }
}

int search_type4(char *line, char **word_v) {
    char *tmp = line;
    int line_size = str_length(line);
    int word1_size = str_length(word_v[0]);
    int word2_size = str_length(word_v[1]);
    for (int i = 0; i < line_size; i++) {
        // if (line[i] != word_v[0][0])
        if(!charcmp(line[i], word_v[0][0]))
            continue;
        // 단어 시작 제약: 단어(His) 중간(is)에서 시작하면 안됨.
        if (i != 0 && line[i - 1] != ' ')
            continue;

        int j;
        for (j = 0; j < word1_size; j++) {
            // if (line[i + j] != word_v[0][j])
            if(!charcmp(line[i+j], word_v[0][j]))
                break;
        }
        if (j != word1_size)
            continue;

        if (line[i + j] != ' ' && line[i + j] != '\n' &&
            line[i + j] != '\0') // && line[i+j] != ')') // 단어 끝 제약: 단어(your) 중간에 끝나는
                                 // 단어(you)를 입력하면 안찾음
            continue;

        int k = i + j + 1;
        while(line[k] == ' ')
            k++;
        for (k = k + 1; k < line_size; k++) {
            // if (line[k] != word_v[1][0])
            if(!charcmp(line[k], word_v[1][0]))
                continue;

            if (line[k - 1] !=
                ' ') // 단어 시작 제약: 단어(His) 중간(is)에서 시작하면 안됨.
                continue;

            int l;
            for (l = 0; l < word2_size; l++) {
                // if (line[k + l] != word_v[1][l])
                if(!charcmp(line[k+l], word_v[1][l]))
                    break;
            }
            if (l != word2_size)
                continue;

            if (line[k + l] != ' ' && line[k + l] != '\n' &&
                line[k + l] != '\0') // && line[k+l] != ')') // 단어 끝 제약: 단어(your) 중간에 끝나는
                                     // 단어(you)를 입력하면 안찾음
                continue;

            return 1;
        }
    }
    return 0;
}