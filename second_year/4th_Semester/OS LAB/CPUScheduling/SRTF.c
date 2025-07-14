#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define maxProcess 100

typedef struct Process_struct Process;
struct Process_struct {
    char pid[10];
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int order; // Input order for FCFS tie-breaker
};

typedef struct Gantt_entry Gantt;
struct Gantt_entry {
    char pid[10];
    int start, finish;
};

// Comparator for sorting by arrival time and input order
int compareByArrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    if(p1->arrivalTime != p2->arrivalTime)
        return p1->arrivalTime - p2->arrivalTime;
    return p1->order - p2->order;
}

// Find process with shortest remaining time (with tie-breakers)
int findNextProcess(Process proc[], int n, int currentTime) {
    int selectedIndex = -1;
    int minRemaining = INT_MAX;
    int minArrival = INT_MAX;
    int minOrder = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
            // First criteria: remaining time
            if(proc[i].remainingTime < minRemaining) {
                minRemaining = proc[i].remainingTime;
                minArrival = proc[i].arrivalTime;
                minOrder = proc[i].order;
                selectedIndex = i;
            }
            // Tie-breaker 1: arrival time
            else if(proc[i].remainingTime == minRemaining) {
                if(proc[i].arrivalTime < minArrival) {
                    minArrival = proc[i].arrivalTime;
                    minOrder = proc[i].order;
                    selectedIndex = i;
                }
                // Tie-breaker 2: input order
                else if(proc[i].arrivalTime == minArrival) {
                    if(proc[i].order < minOrder) {
                        minOrder = proc[i].order;
                        selectedIndex = i;
                    }
                }
            }
        }
    }
    return selectedIndex;
}

void displayGantt(Gantt gantt[], int ganttIndex, int totalWaiting, int totalTurnaround, int n) {
    printf("\nGantt Chart:\n");
    for(int i=0; i<ganttIndex; i++) {
        printf("%s (%d-%d)", gantt[i].pid, gantt[i].start, gantt[i].finish);
        if(i != ganttIndex-1) printf(" | ");
    }
    printf("\n\nAverage Waiting Time: %.2f\n", (float)totalWaiting/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround/n);
}

void SRTF_Scheduling(Process proc[], int n) {
    qsort(proc, n, sizeof(Process), compareByArrival);
    
    int currentTime = 0;
    int remaining = n;
    Gantt gantt[1000];
    int ganttIndex = 0;
    int startTime = 0;
    int prevIndex = -1;

    while(remaining > 0) {
        int selectedIndex = findNextProcess(proc, n, currentTime);
        
        // Handle idle time if no process available
        if(selectedIndex == -1) {
            currentTime++;
            continue;
        }

        // Record context switch in Gantt chart
        if(prevIndex != selectedIndex) {
            if(prevIndex != -1) {
                gantt[ganttIndex].start = startTime;
                gantt[ganttIndex].finish = currentTime;
                strcpy(gantt[ganttIndex].pid, proc[prevIndex].pid);
                ganttIndex++;
            }
            startTime = currentTime;
            prevIndex = selectedIndex;
        }

        // Execute process for 1 time unit
        proc[selectedIndex].remainingTime--;
        currentTime++;

        // Handle process completion
        if(proc[selectedIndex].remainingTime == 0) {
            proc[selectedIndex].completionTime = currentTime;
            remaining--;
            
            // Update Gantt for completed process
            gantt[ganttIndex].start = startTime;
            gantt[ganttIndex].finish = currentTime;
            strcpy(gantt[ganttIndex].pid, proc[selectedIndex].pid);
            ganttIndex++;
            
            prevIndex = -1;
        }
    }

    // Calculate metrics
    int totalWaiting = 0, totalTurnaround = 0;
    for(int i=0; i<n; i++) {
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        totalWaiting += proc[i].waitingTime;
        totalTurnaround += proc[i].turnaroundTime;
    }

    displayGantt(gantt, ganttIndex, totalWaiting, totalTurnaround, n);
}

int main() {
    printf("Preemptive Shortest Remaining Time First (SRTF)\n");
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[maxProcess];
    for(int i=0; i<n; i++) {
        printf("Enter processID, arrival time and burst time for process %d: ", i+1);
        scanf("%s %d %d", proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].order = i; // Track input order
    }

    SRTF_Scheduling(proc, n);
    return 0;
}