#include<stdio.h>
#include<stdlib.h>

void heapfy(int *arr , int n, int i){
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && arr[smallest] > arr[left]){
        smallest = left;
    }

    if(right < n && arr[smallest] > arr[right]){
        smallest = right;
    }

    if(i != smallest){
        int t = arr[smallest];
        arr[smallest] = arr[i];
        arr[i] = t;
        heapfy(arr, n , smallest);
    }
}

int delete(int *arr , int *size){
    arr[0] = arr[(*size)-1];
    *size -= 1;
    for(int i=(*size)/2 ; i>= 0 ; i--){
        heapfy(arr ,*size , i);
    } 
}

void makeHeap(int *arr , int size){
    for(int i=size/2 ; i>=0 ; i--){
        heapfy(arr , size , i);
    }
}

int minTime(int *arr , int n){
    int min = 0;
    makeHeap(arr , n);
    int size = n;
    for(int i=0 ; i<size ; i++){
        min += arr[0]*(size-i);
        delete(arr , &n);
    }
    return min;
}

int main(){
    int n;
    printf("Enter total no of jobs : ");
    scanf("%d",&n);

    int *arr = (int *) calloc (n , sizeof(int));
    for(int i=0 ; i<n ; i++){
        scanf("%d",&arr[i]);
    }

    int t = minTime(arr , n);
    printf("minimum  time to do all jobs with one processor : %d",t);
    return 0;
}