#include<stdio.h>
#include<stdlib.h>

void heapify(int *arr , int n , int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[smallest] > arr[left]){
        smallest = left;
    }

    if(right < n && arr[smallest] > arr[right]){
        smallest = right;
    }

    if(smallest != i){
        int t = arr[smallest];
        arr[smallest] = arr[i];
        arr[i] = t;
        heapify(arr , n , smallest);
    }
}

void delete(int *arr , int *n, int i){
    if(n == 0){
        return ;
    }
    arr[i] = arr[(*n)-1];
    *n = *n - 1;
    for(int i=(*n)/2 ; i >= 0 ; i--){
        heapify(arr, *n , i);
    }
}

int minCompute(int *arr , int *n){
    int minimum = 0;
    if(*n == 0){
        return minimum;
    }
    int t = *n;
    int min;
    for(int i=0 ; i<t ; i++){
        if(i == 0 || i == 1){
            min = arr[0];
            minimum += (t-1) * min;
            delete(arr , n , 0);
        }else{
            min = arr[0];
            minimum += (t-i) * min;
            delete(arr , n , 0);
        }
    }
    printf("\n");
    return minimum;
}

void print(int *arr , int n){
    printf("elements : ");
    for(int i=0 ; i<n ;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter no of files : ");
    scanf("%d",&n);
    int *arr = (int *) calloc (n , sizeof(int));
    printf("Enter files computation time : ");
    for(int i=0 ; i<n ;i++){
        scanf("%d",&arr[i]);
    }

    print(arr , n);
    for(int i=n/2 ; i >= 0 ; i--){
        heapify(arr , n , i);
    }
    print(arr , n);

    int t = minCompute(arr , &n);
    printf("minimum computation for this : %d",t);
    return 0;
}