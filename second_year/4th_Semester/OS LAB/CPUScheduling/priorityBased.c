#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define maxProcess 100

// Preemptive Priority Scheduling
typedef struct Process_struct Process;
struct Process_struct {
    char pid[10];
    int arrivalTime;
    int burstTime;
    int priority;        // Lower value = higher priority
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int order;           // Input order for FCFS tie-breaker
};

typedef struct Gantt_entry Gantt;
struct Gantt_entry {
    char pid[10];
    int start, finish;
};

// Initial sorting comparator (arrival time -> input order)
int compareByArrival(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    if(p1->arrivalTime != p2->arrivalTime)
        return p1->arrivalTime - p2->arrivalTime;
    return p1->order - p2->order;
}

// Find highest priority available process with tie-breakers
int findNextProcess(Process proc[], int n, int currentTime, int currentPID) {
    int selectedIndex = -1;
    int highestPriority = INT_MAX;
    int earliestArrival = INT_MAX;
    int earliestOrder = INT_MAX;

    for(int i=0; i<n; i++) {
        if(proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0) {
            // Higher priority found (lower number)
            if(proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                earliestArrival = proc[i].arrivalTime;
                earliestOrder = proc[i].order;
                selectedIndex = i;
            }
            // Priority tie-breaker
            else if(proc[i].priority == highestPriority) {
                // First check arrival time
                if(proc[i].arrivalTime < earliestArrival) {
                    earliestArrival = proc[i].arrivalTime;
                    earliestOrder = proc[i].order;
                    selectedIndex = i;
                }
                // Final tie-breaker: input order
                else if(proc[i].arrivalTime == earliestArrival && 
                        proc[i].order < earliestOrder) {
                    earliestOrder = proc[i].order;
                    selectedIndex = i;
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

void Priority_Scheduling(Process proc[], int n) {
    qsort(proc, n, sizeof(Process), compareByArrival);
    
    int currentTime = 0;
    int remaining = n;
    Gantt gantt[1000];
    int ganttIndex = 0;
    int currentPID = -1;
    int startTime = 0;

    while(remaining > 0) {
        int selectedIndex = findNextProcess(proc, n, currentTime, currentPID);
        
        // Handle idle time if no process available
        if(selectedIndex == -1) {
            currentTime++;
            continue;
        }

        // Record context switch in Gantt chart
        if(currentPID != selectedIndex) {
            if(currentPID != -1) {
                gantt[ganttIndex].start = startTime;
                gantt[ganttIndex].finish = currentTime;
                strcpy(gantt[ganttIndex].pid, proc[currentPID].pid);
                ganttIndex++;
            }
            startTime = currentTime;
            currentPID = selectedIndex;
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
            
            currentPID = -1;
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
    printf("Preemptive Priority Scheduling\n");
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[maxProcess];
    for(int i=0; i<n; i++) {
        printf("Enter processID, arrival, burst, and priority (lower=higher) for process %d: ", i+1);
        scanf("%s %d %d %d", proc[i].pid, &proc[i].arrivalTime, 
              &proc[i].burstTime, &proc[i].priority);
        proc[i].remainingTime = proc[i].burstTime;
        proc[i].order = i; // Track input order
    }

    Priority_Scheduling(proc, n);
    return 0;
}