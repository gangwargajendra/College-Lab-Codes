#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define maxProcess 100

typedef struct Process_struct Process;
struct Process_struct{
    char pid[10];
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int startTime;
};

typedef struct Gantt_entry Gantt;
struct Gantt_entry{
    char pid[10];
    int start, finish;
};

void displayGantt(Gantt gantt[], int ganttIndex, int totalWaitingTime, int totalTurnAroundTime, int n){
    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++) {
        printf("%s (%d-%d)", gantt[i].pid, gantt[i].start, gantt[i].finish);
        if (i != ganttIndex - 1)
            printf(" | ");
    }
    printf("\n");

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);
}

void SJF(Process proc[], int n){
    int completed = 0, time = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int isCompleted[maxProcess] = {0};
    Gantt gantt[maxProcess];
    int ganttIndex = 0;

    while(completed != n){
        int idx = -1;
        int minBurst = INT_MAX;

        // for finding the process
        for(int i=0 ; i<n ; i++){
            if(proc[i].arrivalTime <= time && isCompleted[i] == 0){
                if(proc[i].burstTime < minBurst){
                    minBurst = proc[i].burstTime;
                    idx = i;
                }
            }
        }

        if(idx != -1){
            // for process  scheduling
            proc[idx].startTime = time;
            int finishTime = time + proc[idx].burstTime;
            proc[idx].completionTime = finishTime;
            proc[idx].turnaroundTime = finishTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].startTime - proc[idx].arrivalTime;

            totalWaitingTime += proc[idx].waitingTime;
            totalTurnAroundTime += proc[idx].turnaroundTime;

            // for gantt chart
            strcpy(gantt[ganttIndex].pid, proc[idx].pid);
            gantt[ganttIndex].start = time;
            gantt[ganttIndex].finish = finishTime;
            ganttIndex++;

            time = finishTime;
            isCompleted[idx] = 1;
            completed ++;
        }else {
            time++;
        }
    }

    displayGantt(gantt, ganttIndex, totalWaitingTime, totalTurnAroundTime, n);
}

int main(){
    printf("Non-preemptive Shortest Job First (SJF)\n");

    int n;
    printf("Enter the number of processess : ");
    scanf("%d",&n);

    Process proc[maxProcess];
    for(int i=0; i<n ; i++){
        printf("Enter the processID, Arrival time and Burst time of process %d : ", i+1);
        scanf("%s %d %d", proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);

        proc[i].waitingTime = 0;
        proc[i].turnaroundTime = 0;
        proc[i].completionTime = 0;
        proc[i].startTime = 0;
    }

    SJF(proc, n);

    return 0;
}