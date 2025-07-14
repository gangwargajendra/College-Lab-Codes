#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096 
#define MEM_SIZE 262144
#define NUM_FRAMES (MEM_SIZE / PAGE_SIZE)
#define MAX_PAGES 1024 

typedef struct pageTableEntry PageTableEntry; 
struct pageTableEntry {
    int frame;
    int valid;
};

PageTableEntry pageTable[MAX_PAGES]; 

void initializeSystem() {
    for (int pageIdx = 0; pageIdx < MAX_PAGES; pageIdx++) {
        pageTable[pageIdx].valid = 1;
        pageTable[pageIdx].frame = pageIdx % NUM_FRAMES;
    }
}

void translateLogicalAddress(int logicalAdd) {
    int pageNumber = logicalAdd / PAGE_SIZE;
    int offset = logicalAdd % PAGE_SIZE;

    if (pageNumber >= MAX_PAGES) {
        printf("Error: Invalid page number (%d). Maximum allowed is %d.\n", pageNumber, MAX_PAGES - 1);
        return;
    }

    int physAdd = pageTable[pageNumber].frame * PAGE_SIZE + offset;
    printf("Physical Address: %d (Frame %d)\n", physAdd, pageTable[pageNumber].frame);
}

int main() {
    initializeSystem();

    translateLogicalAddress(5000);
    translateLogicalAddress(25000);
    translateLogicalAddress(8192); 
    translateLogicalAddress(300000);

    return 0;
}