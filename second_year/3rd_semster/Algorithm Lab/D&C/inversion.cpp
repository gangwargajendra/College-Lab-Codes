#include <stdio.h>

// Function to count pairs where A[i] > B[j] using divide and conquer
int countPairsRecursive(int A[], int n, int B[], int m) {
    // Base case: If A or B is empty, no pairs can be formed
    if (n == 0 || m == 0) {
        return 0;
    }

    // Divide: Find the middle of A
    int mid = n / 2;

    // Count pairs with A[mid] > B[j] for all j
    int count = 0;
    for (int j = 0; j < m; j++) {
        if (A[mid] > B[j]) {
            count += (m - j);
            break;
        }
    }

    // Conquer: Recur for left and right halves of A
    return count + countPairsRecursive(A, mid, B, m) + countPairsRecursive(A + mid + 1, n - mid - 1, B, m);
}

int main() {
    int A[] = {3, 6, 7, 9};
    int B[] = {1, 2, 5, 8, 10};
    int n = sizeof(A) / sizeof(A[0]);
    int m = sizeof(B) / sizeof(B[0]);

    int result = countPairsRecursive(A, n, B, m);

    printf("Number of valid pairs: %d\n", result);

    return 0;
}
