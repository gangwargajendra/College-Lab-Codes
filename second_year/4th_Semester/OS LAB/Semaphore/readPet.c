#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define READER 0
#define WRITER 1
#define MAX_READERS 5
#define MAX_WRITERS 3

// Peterson's algorithm variables
int flags[2] = {0, 0};  // [reader, writer]
int turn;

// Shared resource
int shared_data = 0;
int reader_count = 0;

// Mutex for reader count
pthread_mutex_t rc_mutex = PTHREAD_MUTEX_INITIALIZER;

void enter_critical_section(int role) {
    flags[role] = 1;
    turn = 1 - role;
    while(flags[1 - role] && turn == 1 - role);
}

void exit_critical_section(int role) {
    flags[role] = 0;
}

void* reader(void* arg) {
    int id = *(int*)arg;
    while(1) {
        // Reader entry protocol
        pthread_mutex_lock(&rc_mutex);
        if(reader_count == 0) {
            enter_critical_section(READER);
        }
        reader_count++;
        pthread_mutex_unlock(&rc_mutex);

        // Reading
        printf("Reader %d read: %d\n", id, shared_data);
        sleep(rand() % 2);

        // Reader exit protocol
        pthread_mutex_lock(&rc_mutex);
        reader_count--;
        if(reader_count == 0) {
            exit_critical_section(READER);
        }
        pthread_mutex_unlock(&rc_mutex);
        
        sleep(rand() % 3);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while(1) {
        // Writer entry protocol
        enter_critical_section(WRITER);
        
        // Writing
        shared_data++;
        printf("Writer %d wrote: %d\n", id, shared_data);
        sleep(rand() % 2);
        
        // Writer exit protocol
        exit_critical_section(WRITER);
        
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int ids[MAX_READERS > MAX_WRITERS ? MAX_READERS : MAX_WRITERS];

    // Initialize Peterson's variables
    flags[READER] = 0;
    flags[WRITER] = 0;
    turn = READER;

    // Create readers
    for(int i=0; i<MAX_READERS; i++) {
        ids[i] = i+1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    // Create writers
    for(int i=0; i<MAX_WRITERS; i++) {
        ids[i] = i+1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Join threads (never reached in this infinite loop)
    for(int i=0; i<MAX_READERS; i++) pthread_join(readers[i], NULL);
    for(int i=0; i<MAX_WRITERS; i++) pthread_join(writers[i], NULL);

    return 0;
}