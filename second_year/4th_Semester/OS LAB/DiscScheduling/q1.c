#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void display(char *algo, int *sequence, int n, int iniPos) {
    int totalSeek = 0;
    printf("\nAlgorithm : %s\n", algo);
    printf("Service sequence: %d", iniPos);
    for (int i=0 ; i<n ; i++) {
        printf(" -> %d", sequence[i]);
        totalSeek += abs((i == 0 ? iniPos : sequence[i-1]) - sequence[i]);
    }
    printf("\nTotal seek time: %d\n", totalSeek);
    printf("Average seek time: %.2f\n", (float)totalSeek / n);
}

void fcfs(int *requestQueue, int n, int iniPos, int *outSequence) {
    for (int i=0; i<n; i++) {
        outSequence[i] = requestQueue[i];
    }
}

void sstf(int *requestQueue, int n, int iniPos, int *outSequence) {
    int *done = (int *) calloc (n, sizeof(int));
    int crntPos = iniPos;
    for(int i=0 ; i<n ; i++) {
        int best = -1, bestDist = INT_MAX;
        for(int j=0 ; j<n ; j++) {
            if (!done[j]) {
                int d = abs(crntPos - requestQueue[j]);
                if (d < bestDist){ 
                    bestDist = d;
                    best = j;
                }
            }
        }
        done[best] = 1;
        outSequence[i] = requestQueue[best];
        crntPos = requestQueue[best];
    }
    free(done);
}

void scan(int *requestQueue, int n, int iniPos, int diskSize, int *outSequence) {
    int *up = (int *) malloc (n * sizeof(int));
    int *down = (int *) malloc (n * sizeof(int));
    int u = 0, d = 0;
    for (int i=0 ; i<n ; i++) {
        if (requestQueue[i] >= iniPos) up[u++] = requestQueue[i];
        else                down[d++] = requestQueue[i];
    }

    for (int i = 0 ; i<u-1 ; i++){
        for (int j=i+1 ; j<u ; j++){
            if (up[i] > up[j]) {
                int t = up[i];
                up[i] = up[j];
                up[j] = t;
            }
        }
    }

    for (int i=0 ; i<d-1 ; i++){
        for (int j=i+1 ; j<d ; j++){
            if (down[i] < down[j]){
                int t = down[i];
                down[i] = down[j];
                down[j] = t;
            }
        }
    }

    int idx = 0;
    for (int i = 0; i < u; i++){
        outSequence[idx++] = up[i];
    }

    if (u > 0 && up[u-1] != diskSize - 1) {
        outSequence[idx++] = diskSize - 1;
    }

    for (int i=0 ; i<d ; i++){
        outSequence[idx++] = down[i];
    }

    if (idx == n+1) {
        for (int i = 0; i < n; i++){
            outSequence[i] = outSequence[i];
        }
    }
    free(up);
    free(down);
}

int main() {
    int diskSize, iniPos, n;
    printf("Enter total number of cylinders on disk : ");
    scanf("%d", &diskSize);
    printf("Enter initial head position (0 to %d): ", diskSize - 1);
    scanf("%d", &iniPos);
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int *requestQueue = (int *) malloc(n * sizeof(int));
    printf("Enter request queue : ");
    for(int i=0 ; i<n ; i++){
        scanf("%d", &requestQueue[i]);
        if(requestQueue[i]<0 || requestQueue[i]>=diskSize) {
            printf("request %d out of range.\n", requestQueue[i]);
            return 1;
        }
    }

    int *sequence = (int *) malloc ((n+1) * sizeof(int));

    // FCFS
    fcfs(requestQueue, n, iniPos, sequence);
    display("FCFS", sequence, n, iniPos);

    // SSTF
    sstf(requestQueue, n, iniPos, sequence);
    display("SSTF", sequence, n, iniPos);

    // SCAN
    scan(requestQueue, n, iniPos, diskSize, sequence);
    display("SCAN", sequence, n, iniPos);

    free(requestQueue);
    free(sequence);
    return 0;
}