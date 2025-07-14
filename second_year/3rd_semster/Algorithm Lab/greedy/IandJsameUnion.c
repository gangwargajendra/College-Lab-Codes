#include<stdio.h>
#include<stdlib.h>

typedef struct pair Pair;
struct pair {
    int st;
    int end;
};

void merge(Pair *arr , int low , int mid , int high){
    int n1 = mid - low + 1 ;
    int n2 = high - mid;
    Pair arr1[n1];
    Pair arr2[n2];
    int i=0 , j=0 , k=low;
    while(i < n1){
        arr1[i].st = arr[low+i].st;
        arr1[i].end = arr[low+i].end;
        i++;
    }
    while(j < n2){
        arr2[j].st = arr[mid+1+j].st;
        arr2[j].end = arr[mid+1+j].end;
        j++;
    }
    i = 0 , j = 0;
    while(i < n1 && j < n2){
        if(arr1[i].st < arr2[j].st){
            arr[k].st = arr1[i].st;
            arr[k].end = arr1[i].end;
            i++ , k++;
        }else if(arr1[i].st > arr2[j].st){
            arr[k].st = arr2[j].st;
            arr[k].end = arr2[j].end;
            j++ , k++;
        }else{
            if(arr1[i].end > arr2[j].end){
                arr[k].st = arr1[i].st;
                arr[k].end = arr1[i].end;
                i++ , k++;
            }else{
                 arr[k].st = arr2[j].st;
                arr[k].end = arr2[j].end;
                j++ , k++;
            }
        }
    }

    while(i < n1){
        arr[k].st = arr1[i].st;
        arr[k].end = arr1[i].end;
        i++ , k++;
    }

    while(j < n2){
        arr[k].st = arr2[j].st;
        arr[k].end = arr2[j].end;
        j++ , k++;
    }
}

void mergeSort(Pair *arr , int low , int high){
    if(high > low){
        int mid = low + (high - low ) / 2;
        mergeSort(arr , low , mid);
        mergeSort(arr , mid+1 , high);
        merge(arr , low , mid , high);
    }
}

int minInterval(Pair *arr , int n){
    int minOverlap = 0;
    int i = 1;
    Pair current = arr[i];
    minOverlap++;
    while(i < n){
        for( ; arr[i].st <= )
    }
}

void print(Pair *arr , int n){
    printf("pair : ");
    for(int i=0 ; i<n ; i++){
        printf("(%d,%d),",arr[i].st,arr[i].end);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter no of interval : ");
    scanf("%d",&n);

    Pair *arr = (Pair *) calloc(n , sizeof(struct pair));
    printf("Enter %d pairs : ",n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i].st);
        scanf("%d",&arr[i].end);
    }

    print(arr , n);
    mergeSort(arr , 0 , n-1);
    print(arr , n);
    
    int t = minInterval(arr , n );

    printf("minimum Interval for same union : %d",t);
    return 0;
}