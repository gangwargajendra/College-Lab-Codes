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
    int remainingTime;
};

typedef struct Gantt_entry Gantt;
struct Gantt_entry{
    char pid[10];
    int start, finish;
};

void displayGantt(Gantt gantt[], int ganttIndex, int totalWaitingTime, int TotalTurnAroundTime, int n){
    printf("\nGantt Chart:\n");
        for (int i = 0; i < ganttIndex; i++) {
            printf("%s (%d-%d)", gantt[i].pid, gantt[i].start, gantt[i].finish);
            if (i != ganttIndex - 1)
                printf(" | ");
        }
        printf("\n");

        printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
        printf("Average Turnaround Time: %.2f\n", (float)TotalTurnAroundTime / n);    
}

void RoundRobin(Process proc[], int n, int q){
    int completed = 0, time = 0;
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int queue[1000];
    int front = 0, rear = 0;
    int inQueue[maxProcess] = {0};

    int minArrival = INT_MAX;
    for(int i=0; i<n ; i++){
        if(proc[i].arrivalTime < minArrival)
            minArrival = proc[i].arrivalTime;
        proc[i].remainingTime = proc[i].burstTime;
    } 

    time = minArrival;

    for(int i=0; i<n ; i++){
        if(proc[i].arrivalTime <= time && proc[i].remainingTime > 0 && inQueue[i] == 0){
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    Gantt gantt[1000];
    int ganttIndex = 0;

    while(completed != n){
        if(front == rear){
            time++;
            for(int i=0 ; i<n ; i++){
                if(proc[i].arrivalTime <= time && proc[i].remainingTime > 0 && inQueue[i] == 0){
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;;
        }

        int idx = queue[front];
        front++;
        inQueue[idx] = 0;

        if(time < proc[idx].arrivalTime)
            time = proc[idx].arrivalTime;
        
        int execTime = (proc[idx].remainingTime < q ? proc[idx].remainingTime : q);

        gantt[ganttIndex].start = time;
        time += execTime;
        gantt[ganttIndex].finish = time;
        strcpy(gantt[ganttIndex].pid, proc[idx].pid);
        ganttIndex++;

        proc[idx].remainingTime -= execTime;

        for(int i=0 ; i<n ; i++){
            if(proc[i].arrivalTime > (time - execTime) && proc[i].arrivalTime <= time && proc[i].remainingTime > 0 && inQueue[i] == 0){
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if(proc[idx].remainingTime > 0){
            queue[rear++] = idx;
            inQueue[idx] = 1;
        }else{
            proc[idx].completionTime = time;
            completed++;
        }

        for(int i=0; i<n ; i++){
            if(proc[i].arrivalTime <= time && proc[i].remainingTime >0 && inQueue[i] == 0){
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }
    }

    for(int i=0 ; i<n ; i++){
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        totalWaitingTime += proc[i].waitingTime;
        totalTurnAroundTime += proc[i].turnaroundTime;
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
        proc[i].remainingTime = proc[i].burstTime;
    }

    int q;
    printf("Enter Time Quantum: ");
    scanf("%d", &q);
    RoundRobin(proc, n, q);

    return 0;
}