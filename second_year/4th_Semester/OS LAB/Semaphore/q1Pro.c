#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
typedef struct data SharedData;
struct data{
    int buffer[BUFFER_SIZE];
    int in;
    int out;
};

SharedData sharedData;
sem_t mutex, empty, full;

void* producerFunction(void* arg) {
    int item = 0;
    while (1) {
        sleep(rand() % 3);
        sem_wait(&empty);
        sem_wait(&mutex);

        sharedData.buffer[sharedData.in] = item;
        printf("Produced: %d at index %d\n", item, sharedData.in);
        sharedData.in = (sharedData.in + 1) % BUFFER_SIZE;
        item++;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumerFunction(void* arg) {
    while (1) {
        sleep(rand() % 3);
        sem_wait(&full);
        sem_wait(&mutex);

        int item = sharedData.buffer[sharedData.out];
        printf("Consumed: %d from index %d\n", item, sharedData.out);
        sharedData.out = (sharedData.out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t proThread, conThread;
    
    sharedData.in = 0;
    sharedData.out = 0;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&proThread, NULL, producerFunction, NULL);
    pthread_create(&conThread, NULL, consumerFunction, NULL);

    pthread_join(proThread, NULL);
    pthread_join(conThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}