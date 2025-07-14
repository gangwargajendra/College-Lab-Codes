#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return ;
}

int cmp(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

// int select(int *arr, int k, int n){
//     int *arra = (int *)calloc(n / 5, sizeof(int *));

//     for (int i = 0; i < n; i++){
//         arra[i] = (int *)calloc(5, sizeof(int));
//     }
//     printf("Partion is done\n");

//     for (int i = 0; i < n / 5; i++){
//         qsort(arra[i], 5, sizeof(int), cmp);
//     }
//     printf("Sorting is done\n");

//     int *arr2 = (int *)calloc(n / 5, sizeof(int));
//     for (int i = 0; i < n / 5; i++){
//         arr2[i] = arra[i][2];
//     }
//     printf("New array is created.\n");

//     int m = select(arr2, n / 10, n / 5);
//     printf("Pivot is selected %d\n", m);

//     int q = 3 * n / 10;
//     if (k == q + 1)
//         return m;
//     else{
//         printf("Partition has starting\n");
//         int j = 0, k = 0;
//         int *x = (int *)calloc(n, sizeof(int));
//         int *y = (int *)calloc(n, sizeof(int));

//         for (int i = 0; i < n; i++){
//             if (arr[i] < m){
//                 x[j++] = arr[i];
//             }
//             else{
//                 y[k++] = arr[i];
//             }
//         }
//         printf("Partition hasbeen done\n");

//         if (k < q + 1){
//             return select(x, k, n);
//         }
//         else{
//             return select(y, k, n);
//         }
//     }
// }

int partition(int* arr, int left, int right, int pivot){
    swap(&arr[pivot], &arr[right]);

    int storeIndex = left;
    for(int j = left; j < right; j++){
        if(arr[j] <= pivot){
            swap(&arr[storeIndex], &arr[j]);
            storeIndex++;
        }
    }

    swap(&arr[right], &arr[storeIndex]);
    return storeIndex;
}

int medianOfFive(int* arr, int n){
    if(n <= 5){
        qsort(arr, n, sizeof(int), cmp);
        return arr[n / 2];
    }
    return 0;
}

// 8 0 1 3 5 2 7 19 28 20

int select (int* arr, int start, int end, int k){
    if(start == end){
        return arr[start];
    }

    int n = end - start + 1;
    int numGroups = (n + 4) / 5;
    int* medians = (int* ) calloc(numGroups, sizeof(int));

    for(int i = 0; i < numGroups; i++){
        int groupSize = (i == numGroups - 1) ? n - i * 5 : 5;
        medians[i] = medianOfFive(&arr[start + i * 5], groupSize);
    }

    int medianOfMedians = select(medians, 0, numGroups - 1, numGroups / 2);
    free(medians);

    int pivotIndex = partition(arr, start, end, medianOfMedians);
    int kIndex = pivotIndex - start + 1;

    if(k == kIndex)     return arr[pivotIndex];
    else if(k < kIndex)     return select(arr, start, pivotIndex - 1, k);
    else    return select(arr, pivotIndex + 1, end, k - kIndex);
}

int main(){
    int n;
    printf("Enter number of size: ");
    scanf("%d", &n);

    int *arr = (int *)calloc(n, sizeof(int));
    printf("Enter elements for array: \n");
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    int k;
    printf("Enter number k: ");
    scanf("%d", &k);

    printf("Kth smallest element in array is %d", select(arr, 0, n - 1, k));

    free(arr);
    return 0;
}