#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

typedef struct data SharedData;
struct data {
    int insideMan, insideWoman, crntGender, mantry, womantry;
    sem_t mutex, man, woman;
};

// 0 = empty, 1 = men , 2 = women.

SharedData sharedData;

void man_leaves(int id){
    sem_wait(&sharedData.mutex);
    sharedData.insideMan--;
    printf("Man with id(%d) leaves and total men are inside the restroom : %d.\n", id, sharedData.insideMan);
    if (sharedData.insideMan == 0) {
        if (sharedData.womantry > 0) {
            printf("Restroom is empty and now waiting women can enter in restroom.\n");
            sharedData.crntGender = 2;
            for (int i = 0; i < sharedData.womantry; i++) {
                sem_post(&sharedData.woman);
            }
        } else {
            sharedData.crntGender = 0;
            printf("Restroom empty.\n");
        }
    }
    sem_post(&sharedData.mutex);
}

void *man_wants_to_enter(void *arg) {
    int id = *(int *)arg;
    while(1) {
        sleep(rand() % 3);
        
        sem_wait(&sharedData.mutex);
        if (sharedData.crntGender == 2 || sharedData.womantry > 0) {
            sharedData.mantry++;
            printf("Man with id(%d) is waiting and total waiting men : %d.\n", id, sharedData.mantry);
            sem_post(&sharedData.mutex);
            sem_wait(&sharedData.man);
            sem_wait(&sharedData.mutex);
            sharedData.mantry--;
        }
        
        sharedData.insideMan++;
        if (sharedData.insideMan == 1){
            sharedData.crntGender = 1;
        }
        sem_post(&sharedData.mutex);
        
        printf("Man with id(%d) enters and total men are inside the restroom : %d.\n", id, sharedData.insideMan);
        sleep(1);
        
        man_leaves(id);
    }
    return NULL;
}

void woman_leaves(int id){
    sem_wait(&sharedData.mutex);
    sharedData.insideWoman--;
    printf("Woman with ID : %d left and total inside woman : %d\n", id, sharedData.insideWoman);
    if (sharedData.insideWoman == 0) {
        if (sharedData.mantry > 0) {
            printf("Restroom is empty and now waiting men can enter in restroom.\n");
            sharedData.crntGender = 1;
            for (int i = 0; i < sharedData.mantry; i++) {
                sem_post(&sharedData.man);
            }
        } else {
            sharedData.crntGender = 0;
            printf("Restroom empty.\n");
        }
    }
    sem_post(&sharedData.mutex);
}

void *woman_wants_to_enter(void *arg) {
    int id = *(int *)arg;
    while(1) {
        sleep(rand() % 5);
        
        sem_wait(&sharedData.mutex);
        if (sharedData.crntGender == 1 || sharedData.mantry > 0) {
            sharedData.womantry++;
            printf("Woman with id(%d) is waiting and total women are waiting : %d.\n", id, sharedData.womantry);
            sem_post(&sharedData.mutex);
            sem_wait(&sharedData.woman);
            sem_wait(&sharedData.mutex);
            sharedData.womantry--;
        }
        
        sharedData.insideWoman++;
        if (sharedData.insideWoman == 1) {
            sharedData.crntGender = 2;
        }
        sem_post(&sharedData.mutex);
        
        printf("Woman with ID(%d) entered and total inside women : %d\n", id, sharedData.insideWoman);
        sleep(1);
        
        woman_leaves(id);
    }
    return NULL;
}

int main() {
    pthread_t manThread[3], womanThread[3];
    int manID[3], womanID[3];
    
    sharedData.insideMan = 0;
    sharedData.insideWoman = 0;
    sharedData.crntGender = 0;
    sharedData.mantry = 0;
    sharedData.womantry = 0;
    sem_init(&sharedData.mutex, 0, 1);
    sem_init(&sharedData.man, 0, 0);
    sem_init(&sharedData.woman, 0, 0);
    
    for(int i=0 ; i<3 ; i++) {
        manID[i] = 1000 + i;
        pthread_create(&manThread[i], NULL, man_wants_to_enter, &manID[i]);
    }
    
    for(int i=0 ; i<3 ; i++) {
        womanID[i] = 2000 + i;
        pthread_create(&womanThread[i], NULL, woman_wants_to_enter, &womanID[i]);
    }

    sleep(5);
    exit(0);

    for(int i=0 ; i<3 ; i++) {
        pthread_join(&womanThread[i], NULL);
    }

    for(int i=0 ; i<3 ; i++) {
        pthread_join(&manThread[i], NULL);
    }
    
    sem_destroy(&sharedData.mutex);
    sem_destroy(&sharedData.man);
    sem_destroy(&sharedData.woman);
    
    return 0;
}