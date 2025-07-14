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
int freeFrames[NUM_FRAMES]; 

void initializeSystem() {
    printf("currently Initializing the system...\n");

    for (int pageIdx = 0; pageIdx < MAX_PAGES; pageIdx++) {
        pageTable[pageIdx].valid = 0;
    }

    for (int frameIdx = 0; frameIdx < NUM_FRAMES; frameIdx++) {
        freeFrames[frameIdx] = 0;
    }

    printf("System initialized.\n\n");
}

int handle_page_fault(int page_num) {
    printf("Handling page fault for page %d...\n", page_num);

    for (int frameIdx = 0; frameIdx < NUM_FRAMES; frameIdx++) {
        if (freeFrames[frameIdx] == 0) {
            freeFrames[frameIdx] = 1;
            pageTable[page_num].frame = frameIdx;
            pageTable[page_num].valid = 1;
            printf("Page %d successfully loaded into frame %d.\n", page_num, frameIdx);
            return frameIdx;
        }
    }

    printf("Error: No free frames available! Cannot load page %d.\n", page_num);
    return -1;
}

void translateLogicalAddress(int logicalAdd) {
    printf("\nTranslating logical address %d...\n", logicalAdd);

    int pageNumber = logicalAdd / PAGE_SIZE;
    int offset = logicalAdd % PAGE_SIZE;

    printf("Logical Address: %d => Page: %d, Offset: %d\n", logicalAdd, pageNumber, offset);

    if (pageNumber >= MAX_PAGES) {
        printf("Error: Invalid page number (%d). Maximum allowed is %d.\n", pageNumber, MAX_PAGES - 1);
        return;
    }

    if (pageTable[pageNumber].valid) {
        int physAdd = pageTable[pageNumber].frame * PAGE_SIZE + offset;
        printf("Physical Address: %d (Frame %d)\n", physAdd, pageTable[pageNumber].frame);
    } else {
        printf("Page Fault Detected for page %d.\n", pageNumber);
        int frame = handle_page_fault(pageNumber);

        if (frame != -1) {
            int physAdd = frame * PAGE_SIZE + offset;
            printf("Physical Address: %d (Frame %d)\n", physAdd, frame);
        }
    }
}

int main() {
    initializeSystem();

    translateLogicalAddress(5000);
    translateLogicalAddress(25000);
    translateLogicalAddress(8192); 
    translateLogicalAddress(300000);

    return 0;
}