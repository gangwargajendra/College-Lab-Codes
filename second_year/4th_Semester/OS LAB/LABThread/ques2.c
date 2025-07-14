#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct PartialArray {
    int *array;
    int startIndex;
    int endIndex;
    long partialSum;
};

void *sum(void *partial_Arr) {
    struct PartialArray *partialArr = (struct PartialArray *)partial_Arr;
    partialArr->partialSum = 0;
    for (int i = partialArr->startIndex; i < partialArr->endIndex; i++) {
        partialArr->partialSum += partialArr->array[i];
    }
    pthread_exit(NULL);
}

int main() {
    int arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 - i;
    }

    pthread_t threadArr[5];
    struct PartialArray partialArr[5];
    long totalSum = 0;

    for (int i = 0; i < 5; i++) {
        partialArr[i].array = arr;
        partialArr[i].startIndex = (i * 1000) / 5;
        partialArr[i].endIndex = ((i + 1) * 1000) / 5;
        pthread_create(&threadArr[i], NULL, sum, &partialArr[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threadArr[i], NULL);
        totalSum += partialArr[i].partialSum;
    }

    printf("Total sum for whole array : %ld\n", totalSum);
    return 0;
}