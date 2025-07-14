#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_SIZE 1024
#define NUM_PAGES 256
#define NUM_FRAMES 128
#define TLB_SIZE 16
#define MEM_ACCESSES 1000


typedef struct pageTableEntry PageTableEntry;
typedef struct tlbEntry TLBEntry;
typedef struct frameTableEntry FrameTableEntry;

struct pageTableEntry{
    int frameNumber;
    int valid;
    int modified;
    int referenced;
};

struct tlbEntry{
    int virtualPage;
    int frameNumber;
    int valid;
    int timeOfUse;
};

struct frameTableEntry{
    int pageNumber;
    int loadedTime;
};

PageTableEntry pageTable[NUM_PAGES];
TLBEntry tlb[TLB_SIZE];
FrameTableEntry frameTable[NUM_FRAMES];
int currentTime = 0;

int tlbHits = 0;
int tlbMisses = 0;
int pageFaults = 0;

void iniMemory() {
    for (int i = 0; i < NUM_PAGES; i++) {
        pageTable[i].valid = 0;
        pageTable[i].modified = 0;
        pageTable[i].referenced = 0;
    }

    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = 0;
    }

    for (int i = 0; i < NUM_FRAMES; i++) {
        frameTable[i].pageNumber = -1;
        frameTable[i].loadedTime = 0;
    }
}

int extractPageNumber(int virtualAddress) {
    return virtualAddress / PAGE_SIZE;
}

int extractOffset(int virtualAddress) {
    return virtualAddress % PAGE_SIZE;
}

int checktlb(int pageNumber) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].virtualPage == pageNumber) {
            tlb[i].timeOfUse = currentTime;
            return tlb[i].frameNumber;
        }
    }
    return -1;
}

void updatetlb(int pageNumber, int frameNumber) {
    int lruIndex = 0;
    int minTime = currentTime;

    for (int i = 0; i < TLB_SIZE; i++) {
        if (!tlb[i].valid) {
            lruIndex = i;
            break;
        }
        if (tlb[i].timeOfUse < minTime) {
            minTime = tlb[i].timeOfUse;
            lruIndex = i;
        }
    }

    tlb[lruIndex].virtualPage = pageNumber;
    tlb[lruIndex].frameNumber = frameNumber;
    tlb[lruIndex].valid = 1;
    tlb[lruIndex].timeOfUse = currentTime;
}

int handlePageFault(int pageNumber) {
    pageFaults++;
    int frameNumber = -1;

    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frameTable[i].pageNumber == -1) {
            frameNumber = i;
            break;
        }
    }

    if (frameNumber == -1) {
        int oldest = currentTime;
        for (int i = 0; i < NUM_FRAMES; i++) {
            if (frameTable[i].loadedTime < oldest) {
                oldest = frameTable[i].loadedTime;
                frameNumber = i;
            }
        }

        int evictedPage = frameTable[frameNumber].pageNumber;
        pageTable[evictedPage].valid = 0;
    }

    frameTable[frameNumber].pageNumber = pageNumber;
    frameTable[frameNumber].loadedTime = currentTime;

    pageTable[pageNumber].frameNumber = frameNumber;
    pageTable[pageNumber].valid = 1;
    pageTable[pageNumber].referenced = 1;

    return frameNumber;
}

int translateAddress(int virtualAddress) {
    currentTime++;
    int pageNumber = extractPageNumber(virtualAddress);
    int offset = extractOffset(virtualAddress);

    int frameNumber = checktlb(pageNumber);
    if (frameNumber != -1) {
        tlbHits++;
        return (frameNumber * PAGE_SIZE) + offset;
    }

    tlbMisses++;

    if (pageTable[pageNumber].valid) {
        frameNumber = pageTable[pageNumber].frameNumber;
    } else {
        frameNumber = handlePageFault(pageNumber);
    }

    updatetlb(pageNumber, frameNumber);

    return (frameNumber * PAGE_SIZE) + offset;
}

void generateMemoryAccesses() {
    srand(time(NULL));
    for (int i = 0; i < MEM_ACCESSES; i++) {
        int virtualAddress;
        
        if (i % 3 == 0) { 
            virtualAddress = (i * PAGE_SIZE) % (NUM_PAGES * PAGE_SIZE);
        } else if (i % 3 == 1) {
            virtualAddress = rand() % (NUM_PAGES * PAGE_SIZE);
        } else { 
            int base = rand() % (NUM_PAGES - 10);
            virtualAddress = (base + (i % 10)) * PAGE_SIZE;
        }
        
        translateAddress(virtualAddress);
    }
}

void printStatistics() {
    printf("TLB Hits: %d\n", tlbHits);
    printf("TLB Misses: %d\n", tlbMisses);
    printf("Page Faults: %d\n", pageFaults);
    printf("TLB Hit Rate: %.2f%%\n", (float)tlbHits / (tlbHits + tlbMisses) * 100);
    printf("Average Memory Access Time: %.2f\n", 
          (tlbHits+ tlbMisses * (1 + 100)) / (float)MEM_ACCESSES);
}

int main() {
    iniMemory();
    generateMemoryAccesses();
    printStatistics();
    return 0;
}