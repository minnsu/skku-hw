#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    FILE *fpr = fopen(argv[1], "r");
    // READ
    size_t len = 0;
    ssize_t read;
    int size;
    char** line = new char*[100];
    read = getline(&line[0], &len, fpr);
    size = atoi(line[0]);
    for(int i = 1; i <= size; i++){
        line[i] = new char[100];
        read = getline(&line[i], &len, fpr);
    }
    fclose(fpr);

    
    FILE *fpw = fopen(argv[2], "w");
    // Solve and Write
    for(int i = 0; i < size; i++){
        fprintf(fpw, "%s", line[i]);
    }
    fclose(fpw);
}