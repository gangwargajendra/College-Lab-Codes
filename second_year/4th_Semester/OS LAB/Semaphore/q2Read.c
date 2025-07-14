#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct data SharedData;
struct data{
    int readcount;
    sem_t mutex, wrt, read_try;
};

SharedData sharedData;

void* writerFunction(void* arg) {
    while (1) {
        sleep(rand() % 5); 
        sem_wait(&sharedData.read_try);
        sem_wait(&sharedData.wrt);

        printf("Writing \n");
        sleep(2);

        sem_post(&sharedData.wrt);
        sem_post(&sharedData.read_try);
    }
    return NULL;
}

void* readerFunction(void* arg) {
    while (1) {
        sleep(rand() % 3);
        sem_wait(&sharedData.read_try);
        sem_wait(&sharedData.mutex);
        
        sharedData.readcount++;
        if (sharedData.readcount == 1) {
            sem_wait(&sharedData.wrt);
        }
        sem_post(&sharedData.mutex);
        sem_post(&sharedData.read_try);

        printf("Reading (readers : %d)\n", sharedData.readcount);
        sleep(1);

        sem_wait(&sharedData.mutex);
        sharedData.readcount--;
        if (sharedData.readcount == 0) {
            sem_post(&sharedData.wrt);
        }
        sem_post(&sharedData.mutex);
    }
    return NULL;
}

int main() {
    pthread_t writerThread, readerThread[3];
    
    sharedData.readcount = 0;
    sem_init(&sharedData.mutex, 0, 1);
    sem_init(&sharedData.wrt, 0, 1);
    sem_init(&sharedData.read_try, 0, 1);

    pthread_create(&writerThread, NULL, writerFunction, NULL);
    for(int i = 0; i < 3; i++) {
        pthread_create(&readerThread[i], NULL, readerFunction, NULL);
    }

    pthread_join(writerThread, NULL);
    for(int i = 0; i < 3; i++) {
        pthread_join(readerThread[i], NULL);
    }

    sem_destroy(&sharedData.mutex);
    sem_destroy(&sharedData.wrt);
    sem_destroy(&sharedData.read_try);

    return 0;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_men = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_women = PTHREAD_COND_INITIALIZER;

int count_men = 0;
int count_women = 0;
int waiting_men = 0;
int waiting_women = 0;

typedef enum { NONE, MEN, WOMEN } Gender;
Gender current_gender = NONE;

void man_wants_to_enter(int id) {
    pthread_mutex_lock(&mutex);
    printf("Man %d wants to enter.\n", id);
    while (current_gender == WOMEN || (current_gender == NONE && waiting_women > 0)) {
        waiting_men++;
        pthread_cond_wait(&cond_men, &mutex);
        waiting_men--;
    }
    current_gender = MEN;
    count_men++;
    printf("Man %d enters. Men inside: %d\n", id, count_men);
    pthread_mutex_unlock(&mutex);
}

void man_leaves(int id) {
    pthread_mutex_lock(&mutex);
    count_men--;
    printf("Man %d leaves. Men inside: %d. ", id, count_men);
    if (count_men == 0 && count_women == 0) {
        current_gender = NONE;
        printf("Restroom empty.\n");
        if (waiting_women > 0) {
            current_gender = WOMEN;
            pthread_cond_broadcast(&cond_women);
        } else if (waiting_men > 0) {
            current_gender = MEN;
            pthread_cond_broadcast(&cond_men);
        }
    } else {
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);
}

void woman_wants_to_enter(int id) {
    pthread_mutex_lock(&mutex);
    printf("Woman %d wants to enter.\n", id);
    while (current_gender == MEN || (current_gender == NONE && waiting_men > 0)) {
        waiting_women++;
        pthread_cond_wait(&cond_women, &mutex);
        waiting_women--;
    }
    current_gender = WOMEN;
    count_women++;
    printf("Woman %d enters. Women inside: %d\n", id, count_women);
    pthread_mutex_unlock(&mutex);
}

void woman_leaves(int id) {
    pthread_mutex_lock(&mutex);
    count_women--;
    printf("Woman %d leaves. Women inside: %d. ", id, count_women);
    if (count_men == 0 && count_women == 0) {
        current_gender = NONE;
        printf("Restroom empty.\n");
        if (waiting_men > 0) {
            current_gender = MEN;
            pthread_cond_broadcast(&cond_men);
        } else if (waiting_women > 0) {
            current_gender = WOMEN;
            pthread_cond_broadcast(&cond_women);
        }
    } else {
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);
}

void* man_thread(void* arg) {
    int id = *(int*)arg;
    man_wants_to_enter(id);
    sleep(1); // Simulate using restroom
    man_leaves(id);
    return NULL;
}

void* woman_thread(void* arg) {
    int id = *(int*)arg;
    woman_wants_to_enter(id);
    sleep(1); // Simulate using restroom
    woman_leaves(id);
    return NULL;
}

int main() {
    pthread_t threads[10];
    int ids[] = {0,1,2,3,4,5,6,7,8,9};
    
    // Create 5 men and 5 women threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, man_thread, &ids[i]);
        pthread_create(&threads[i+5], NULL, woman_thread, &ids[i+5]);
    }
    
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}