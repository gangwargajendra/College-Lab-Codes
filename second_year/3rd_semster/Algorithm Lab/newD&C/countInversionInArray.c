#include<stdio.h>
#include<stdlib.h>

int mergeAndCount(int *arr, int *temp, int left, int mid, int right) {
    int i = left;   
    int j = mid + 1; 
    int k = left;    
    int inversion = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversion += (mid - i + 1); 
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    return inversion;
}


// int countInversion(int *arr, int *temp, int left, int right) {
//     int inversion = 0;

//     if (left < right) {
//         int mid = (left + right) / 2;

//         // Count inversions in the left and right halves
//         inversion += countInversion(arr, temp, left, mid);
//         inversion += countInversion(arr, temp, mid + 1, right);

//         // Count inversions while merging the two halves
//         inversion += mergeAndCount(arr, temp, left, mid, right);
//     }

//     return inversion;
// }

int countInversion(int *a ,int *temp , int st , int end){
    if(st <= end){
        if(st == end){
            return 0;
        }
        int mid = (st + end) / 2;
        int leftInversion = countInversion(a , temp,st, mid);
        int rightInversion = countInversion(a ,temp, mid+1 , end);

        int inversion = mergeAndCount(a ,temp, st ,mid , end);
        return (inversion + leftInversion + rightInversion);
    }
}

int main(){
    int n;
    printf("Emter size : ");
    scanf("%d",&n);

    int a[n];
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }

    int *temp =(int *) calloc (n , sizeof(int));

    int inve = countInversion(a ,temp,  0,n-1);
    printf("inversion = %d",inve);
    return 0;
}



