#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to count the number of bits set in a mask
int count_bits(int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

// This function checks if all processes (except those excluded) can finish
int can_finish(int n, int m, int *available, int **alloc, int **request, int *excluded) {
    int *finish = (int *)calloc(n, sizeof(int));
    int *work = (int *)malloc(m * sizeof(int));
    memcpy(work, available, m * sizeof(int));

    int progress;
    do {
        progress = 0;
        for (int i = 0; i < n; i++) {
            if (excluded[i] || finish[i])
                continue;
            int can_allocate = 1;
            for (int j = 0; j < m; j++) {
                if (request[i][j] > work[j]) {
                    can_allocate = 0;
                    break;
                }
            }
            if (can_allocate) {
                // Process i can finish, so release its allocated resources.
                for (int j = 0; j < m; j++) {
                    work[j] += alloc[i][j];
                }
                finish[i] = 1;
                progress = 1;
            }
        }
    } while (progress);

    int all_finished = 1;
    for (int i = 0; i < n; i++) {
        if (!excluded[i] && !finish[i]) {
            all_finished = 0;
            break;
        }
    }

    free(finish);
    free(work);
    return all_finished;
}

int main() {
    int m, n;
    
    // Input for resource types and their instances
    printf("Enter the number of resource types (m): ");
    scanf("%d", &m);
    
    int *instances = (int *)malloc(m * sizeof(int));
    printf("Enter the total instances for each resource type (separated by spaces):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &instances[i]);
    }
    
    // Input for processes and matrices
    printf("Enter the number of processes (n): ");
    scanf("%d", &n);
    
    // Allocate memory for allocation and request matrices
    int **alloc = (int **)malloc(n * sizeof(int *));
    int **request = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        alloc[i] = (int *)malloc(m * sizeof(int));
        request[i] = (int *)malloc(m * sizeof(int));
    }
    
    // Read the allocation matrix
    printf("Enter the Allocation matrix (each row has %d integers):\n", m);
    for (int i = 0; i < n; i++) {
        printf("Allocation for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    // Read the request matrix
    printf("Enter the Request matrix (each row has %d integers):\n", m);
    for (int i = 0; i < n; i++) {
        printf("Request for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }
    
    // Calculate the initially available resources: total instances minus allocated ones.
    int *available_initial = (int *)malloc(m * sizeof(int));
    for (int r = 0; r < m; r++) {
        available_initial[r] = instances[r];
        for (int i = 0; i < n; i++) {
            available_initial[r] -= alloc[i][r];
        }
    }
    
    // Check if a deadlock exists without terminating any process
    int *excluded = (int *)calloc(n, sizeof(int)); // Initially, no process is excluded.
    int initial_deadlock = !can_finish(n, m, available_initial, alloc, request, excluded);
    free(excluded);
    
    if (!initial_deadlock) {
        printf("No deadlock detected.\n");
    } else {
        // Try to find the minimal set of processes to terminate so that all others can finish.
        int found = 0;
        for (int k = 1; k <= n && !found; k++) {
            // Iterate over all subsets of processes (using bit masking)
            for (int mask = 0; mask < (1 << n) && !found; mask++) {
                if (count_bits(mask) != k)
                    continue;
    
                int *excluded_subset = (int *)calloc(n, sizeof(int));
                int *sum_S = (int *)calloc(m, sizeof(int));
                // Build the current excluded set and compute the resources freed by terminating them.
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        excluded_subset[i] = 1;
                        for (int r = 0; r < m; r++) {
                            sum_S[r] += alloc[i][r];
                        }
                    }
                }
                
                int *new_available = (int *)malloc(m * sizeof(int));
                for (int r = 0; r < m; r++) {
                    new_available[r] = available_initial[r] + sum_S[r];
                }
                
                // Check if the remaining processes can finish with the new available resources.
                int can = can_finish(n, m, new_available, alloc, request, excluded_subset);
                free(sum_S);
                free(new_available);
                
                if (can) {
                    printf("Deadlock exists.\n");
                    printf("The minimal set of processes to terminate is:");
                    for (int i = 0; i < n; i++) {
                        if (excluded_subset[i]) {
                            printf(" P%d", i);
                        }
                    }
                    printf("\n");
                    found = 1;
                }
                free(excluded_subset);
            }
        }
        if (!found) {
            printf("Deadlock exists.\nNo solution found (should not happen).\n");
        }
    }
    
    // Free all allocated memory
    for (int i = 0; i < n; i++) {
        free(alloc[i]);
        free(request[i]);
    }
    free(alloc);
    free(request);
    free(instances);
    free(available_initial);
    
    return 0;
}
