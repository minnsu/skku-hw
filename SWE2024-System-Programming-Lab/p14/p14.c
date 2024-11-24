#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QSIZE 5
#define LOOP 30

typedef struct {
    int put_index; // rear
    int get_index; // front
    int length;    // size
    int capacity;
    int n_loops;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
    int data[];
} queue_t;

void* produce(void* args);
void* consume(void* args);
void put_data(queue_t* queue, int data);
int get_data(queue_t* queue);

queue_t* qinit(int capacity, int n_loops) {
    queue_t* queue = (queue_t*) malloc(sizeof(queue_t) + sizeof(int[capacity]));
    queue->capacity = capacity;
    queue->n_loops = n_loops;
    queue->put_index = queue->get_index = queue->length = 0;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    return queue;
}

void qdelete(queue_t* queue) {
    pthread_mutex_destroy(&queue->lock);
    pthread_cond_destroy(&queue->not_full);
    pthread_cond_destroy(&queue->not_empty);
    free(queue);
}

int main() {
    queue_t* queue = qinit(QSIZE, LOOP);

    pthread_t producer, consumer;
    pthread_create(&producer, NULL, produce, (void *)queue);
    pthread_create(&consumer, NULL, consume, (void *)queue);

    pthread_join (producer, NULL);
    pthread_join (consumer, NULL);

    qdelete(queue);
}

void* produce(void* args) {
    int i, data;
    queue_t* queue = (queue_t*)args;
    for (i = 0; i < queue->n_loops; i++) {
        data = i;
        put_data(queue, data);
        printf("put data %d to queue\n", data);
    }
    pthread_exit(NULL);
}

void* consume(void *args) {
    int i;
    queue_t* queue = (queue_t*)args;
    for (i = 0; i < queue->n_loops; i++) {
        printf("get data %d from queue\n", get_data(queue));
    }
    pthread_exit(NULL);
}

/** Add your code here **/

// Put data unless queue is full
void put_data(queue_t* queue, int data) {
    // 1. Lock
    // 2. Wait until `length` is less than `queue->capacity`
    // 3. Put Algorithm for Circular Array
    // 3.a. Wait until queue is not full  (Fulfilled by 2.)
    // 3.b. Assign value `d` to the position pointed by `put_index`
    // 3.c.i. Increase `put_data` index by 1
    // 3.c.ii. When `put_index` reaches `queue->capacity`, go back to zero
    // 3.d. Increase `length` by 1
    // 4. Unlock
    // 5. Tell `get_data` that queue is not empty
    pthread_mutex_lock(&queue->lock);
    while(queue->length == queue->capacity)
        pthread_cond_wait(&queue->not_full, &queue->lock);
    
    queue->data[queue->put_index] = data;
    queue->put_index = (queue->put_index + 1) % queue->capacity;
    queue->length++;
    pthread_mutex_unlock(&queue->lock);
    pthread_cond_signal(&queue->not_empty);
}

// Get data unless queue is empty
int get_data(queue_t* queue) {
    // 1. Lock
    // 2: Wait until `length` is not zero
    // 3. Get Algorithm for Circular Array
    // 3.a. Wait until queue is not empty (Fulfilled by 2.)
    // 3.b. Get the value at index `get_index` and increase `get_index` by 1
    // 3.c. When `get_index` reaches `queue->capacity`, set `get_index` to 0
    // 3.d. When `length` is zero, set `get_index` and `put_index` to 0
    // 4. Unlock
    // 5. Tell `put_data` that queue is not full
    // 6. Return data
    int data = 0;
    pthread_mutex_lock(&queue->lock);
    while(queue->length == 0)
        pthread_cond_wait(&queue->not_empty, &queue->lock);
    data = queue->data[queue->get_index];
    queue->get_index = (queue->get_index + 1) % queue->capacity;
    queue->length--;
    if(queue->length == 0) {
        queue->get_index = 0;
        queue->put_index = 0;
    }
    pthread_mutex_unlock(&queue->lock);
    pthread_cond_signal(&queue->not_full);
    return data;
}

/** End **/

