#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct ThreadData *Thread;
struct ThreadData {
    int id;
    char *message;
};

void *displayThread(void *arg) {
    struct ThreadData *thread = (struct ThreadData *)arg;
    printf("Thread ID: %d, Message: %s\n", thread->id, thread->message);
    free(thread);
    pthread_exit(NULL);
}

int main() {
    int noOfThread = 8;
    pthread_t threadArray[noOfThread];
    char *messages[] = {"thread 0", "thread 1", "thread 2", "thread 3", "thread 4", "thread 5", "thread 6", "thread 7"};

    for (int i = 0; i < noOfThread; i++) {
        Thread thread = malloc(1 * sizeof(struct ThreadData));
        thread->id = i;
        thread->message = messages[i];
        pthread_create(&threadArray[i], NULL, displayThread, thread);
    }

    for (int i = 0; i < noOfThread; i++) {
        pthread_join(threadArray[i], NULL);
    }

    return 0;
}