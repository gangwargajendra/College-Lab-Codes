#include <stdio.h>
#include<stdlib.h>
#include <limits.h>

int findCrossMaxSubarray(int arr[], int left, int mid, int right) {
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}

int findMaxSubarraySum(int arr[], int left, int right) {
    if (left == right) {
        return arr[left];
    }

    int mid = (left + right) / 2;

    int leftMax = findMaxSubarraySum(arr, left, mid);
    int rightMax = findMaxSubarraySum(arr, mid + 1, right);
    int crossMax = findCrossMaxSubarray(arr, left, mid, right);

    if (leftMax >= rightMax && leftMax >= crossMax) {
        return leftMax;
    } else if (rightMax >= leftMax && rightMax >= crossMax) {
        return rightMax;
    } else {
        return crossMax;
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int maxSum = findMaxSubarraySum(arr, 0, n - 1);
    
    printf("The maximum contiguous subsequence sum is: %d\n", maxSum);
    
    free(arr);
    return 0;
}
