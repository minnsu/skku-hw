#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct thread_data {
        int *row;
        int *vector;
        int N;
        int ret;
};

void *thread(void *arg) {
        struct thread_data *data = (struct thread_data *)arg;
        for(int i = 0; i < data->N; i++) {
                data->ret += data->row[i] * data->vector[i];
        }
        pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
        int M, N;
        M = atoi(argv[1]);
        N = atoi(argv[2]);    

        srand(time(NULL));
        int **matrix = (int **) malloc(sizeof(int *) * M);
        printf(" *** Matrix ***\n");
        for(int i = 0; i < M; i++){
                matrix[i] = (int *) malloc(sizeof(int) * N);
                for(int j = 0; j < N; j++){
                        matrix[i][j] = rand() % 10;
                        printf("[ %d ]", matrix[i][j]);
                        if(j < N-1){
                                printf(" ");
                        }
                }
                printf("\n");
        }

        printf(" *** Vector ***\n");
        int *vector = (int *) malloc(sizeof(int) * N);
        for(int i = 0; i < N; i++){
                vector[i] = rand() % 10;
                printf("[ %d ]\n", vector[i]);
        }

        /* pthread */
        pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * M);
        struct thread_data *data = (struct thread_data *) malloc(sizeof(struct thread_data) * M);
        for(int i = 0; i < M; i++) {
                data[i].row = matrix[i];
                data[i].vector = vector;
                data[i].N = N;
                data[i].ret = 0;
                pthread_create(&tid[i], NULL, thread, (void *)&data[i]);
        }


        for(int i = 0; i < M; i++) {
                pthread_join(tid[i], NULL);
        }

        printf("\n *** Result ***\n");
        for(int i = 0; i < M; i++){
                printf("[ %d ]\n", data[i].ret);
        }

        free(tid);
        free(data);
        for(int i = 1; i < M; i++){
                free(matrix[i]);
        }
        free(matrix);
        free(vector);
        return 0;
}