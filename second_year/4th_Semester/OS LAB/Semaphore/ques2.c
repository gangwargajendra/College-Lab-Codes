#include <stdio.h>
#include <stdbool.h>

#define NUM_FRAMES 4
#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 8 // 2048 addresses (8 pages)

typedef struct {
    int frame;
    bool valid;
} PageTableEntry;

PageTableEntry page_table[PAGE_TABLE_SIZE];
int physical_frames[NUM_FRAMES];
int last_used[NUM_FRAMES];
int page_faults = 0;
int current_time = 0;

void initialize() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].valid = false;
    }
    for (int i = 0; i < NUM_FRAMES; i++) {
        physical_frames[i] = -1;
        last_used[i] = 0;
    }
}

void handle_memory_access(int virtual_address) {
    current_time++;
    int page_number = virtual_address / PAGE_SIZE;
    if (page_number >= PAGE_TABLE_SIZE) {
        printf("Invalid address\n");
        return;
    }
    
    if (page_table[page_number].valid) {
        // Page hit
        int frame = page_table[page_number].frame;
        last_used[frame] = current_time;
    } else {
        // Page fault
        page_faults++;
        int lru_frame = 0;
        int min_time = last_used[0];
        
        // Find LRU frame
        for (int i = 1; i < NUM_FRAMES; i++) {
            if (last_used[i] < min_time) {
                min_time = last_used[i];
                lru_frame = i;
            }
        }
        
        // Replace LRU frame
        int old_page = physical_frames[lru_frame];
        if (old_page != -1) {
            page_table[old_page].valid = false;
        }
        
        physical_frames[lru_frame] = page_number;
        page_table[page_number].frame = lru_frame;
        page_table[page_number].valid = true;
        last_used[lru_frame] = current_time;
    }
}

void print_page_table() {
    printf("Page Table:\n");
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        printf("Page %d: Frame %d, Valid: %d\n", i, 
               page_table[i].frame, page_table[i].valid);
    }
}

int main() {
    initialize();
    int reference_string[] = {0, 512, 256, 0, 128, 256, 512, 0, 128, 640};
    
    for (int i = 0; i < 10; i++) {
        handle_memory_access(reference_string[i]);
    }
    
    print_page_table();
    printf("Total page faults: %d\n", page_faults);
    return 0;
}