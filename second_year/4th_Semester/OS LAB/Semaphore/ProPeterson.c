#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define PRODUCER 0
#define CONSUMER 1

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
    int count;  // Track occupied slots
} SharedData;

SharedData sharedData;

// Peterson's algorithm variables
int flags[2] = {0, 0};
int turn;

// Buffer state tracking
volatile int buffer_empty = 1;
volatile int buffer_full = 0;

void enter_critical_section(int process) {
    flags[process] = 1;
    turn = 1 - process;
    while(flags[1 - process] && turn == 1 - process);
}

void exit_critical_section(int process) {
    flags[process] = 0;
}

void* producer(void* arg) {
    int item = 0;
    while(1) {
        sleep(rand() % 3);
        
        // Wait while buffer is full
        while(buffer_full) {
            usleep(1000);  // Prevent busy-waiting
        }
        
        enter_critical_section(PRODUCER);
        
        // Critical section
        if(sharedData.count < BUFFER_SIZE) {
            sharedData.buffer[sharedData.in] = item;
            printf("Produced: %d at index %d\n", item, sharedData.in);
            sharedData.in = (sharedData.in + 1) % BUFFER_SIZE;
            sharedData.count++;
            item++;
            
            buffer_empty = 0;
            if(sharedData.count == BUFFER_SIZE)
                buffer_full = 1;
        }
        
        exit_critical_section(PRODUCER);
    }
    return NULL;
}

void* consumer(void* arg) {
    while(1) {
        sleep(rand() % 3);
        
        // Wait while buffer is empty
        while(buffer_empty) {
            usleep(1000);  // Prevent busy-waiting
        }
        
        enter_critical_section(CONSUMER);
        
        // Critical section
        if(sharedData.count > 0) {
            int item = sharedData.buffer[sharedData.out];
            printf("Consumed: %d from index %d\n", item, sharedData.out);
            sharedData.out = (sharedData.out + 1) % BUFFER_SIZE;
            sharedData.count--;
            
            buffer_full = 0;
            if(sharedData.count == 0)
                buffer_empty = 1;
        }
        
        exit_critical_section(CONSUMER);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize shared data
    sharedData.in = 0;
    sharedData.out = 0;
    sharedData.count = 0;
    
    // Initialize Peterson's variables
    flags[PRODUCER] = 0;
    flags[CONSUMER] = 0;
    turn = PRODUCER;
    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}