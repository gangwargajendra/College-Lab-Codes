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
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int order; // To maintain input order for tie-breaking
};

typedef struct Gantt_entry Gantt;
struct Gantt_entry {
    char pid[10];
    int start, finish;
};

// Comparator function for sorting processes
int compare(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    
    // Sort by arrival time first
    if(p1->arrivalTime != p2->arrivalTime)
        return p1->arrivalTime - p2->arrivalTime;
    // For same arrival time, sort by input order
    return p1->order - p2->order;
}

void displayGantt(Gantt gantt[], int ganttIndex, int totalWaitingTime, int totalTurnAroundTime, int n) {
    printf("\nGantt Chart:\n");
    for(int i=0; i<ganttIndex; i++) {
        printf("%s (%d-%d)", gantt[i].pid, gantt[i].start, gantt[i].finish);
        if(i != ganttIndex-1) printf(" | ");
    }
    printf("\n");
    
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime/n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime/n);
}

void FCFS_Scheduling(Process proc[], int n) {
    // Sort processes by arrival time and input order
    qsort(proc, n, sizeof(Process), compare);
    
    int currentTime = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    Gantt gantt[maxProcess];
    int ganttIndex = 0;
    
    for(int i=0; i<n; i++) {
        // Handle idle time if no process arrives immediately
        if(currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }
        
        // Create Gantt chart entry
        gantt[ganttIndex].start = currentTime;
        strcpy(gantt[ganttIndex].pid, proc[i].pid);
        gantt[ganttIndex].finish = currentTime + proc[i].burstTime;
        ganttIndex++;
        
        // Calculate metrics
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnaroundTime;
        
        currentTime = proc[i].completionTime;
    }
    
    displayGantt(gantt, ganttIndex, totalWaitingTime, totalTurnAroundTime, n);
}

int main() {
    printf("Non-preemptive First-Come First-Served (FCFS)\n");
    
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process proc[maxProcess];
    for(int i=0; i<n; i++) {
        printf("Enter processID, Arrival time and Burst time of process %d: ", i+1);
        scanf("%s %d %d", proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].order = i; // Maintain input order for tie-breaking
    }
    
    FCFS_Scheduling(proc, n);
    
    return 0;
}