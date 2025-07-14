#include<stdio.h>
#include<stdlib.h>

typedef struct interval Interval;
struct interval {
    int x;
    int y;
};

void print(Interval *arr ,int n){
    printf("interval : ");
    for(int i = 0 ; i < n ; i++){
        printf("[%d,%d],",arr[i].x,arr[i].y);
    }
    printf("\n");
}


void sorting(Interval *arr , int n,int k){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n - i -1 ; j++){
            if(k == 0){
                if(arr[j].x > arr[j+1].x){
                    int x1 = arr[j].x;
                    int y1 = arr[j].y;
                    arr[j].x = arr[j+1].x;
                    arr[j].y = arr[j+1].y;
                    arr[j+1].x = x1;
                    arr[j+1].y = y1;
                }
            }else if(k == 1){
                if(arr[j].y > arr[j+1].y){
                    int x1 = arr[j].x;
                    int y1 = arr[j].y;
                    arr[j].x = arr[j+1].x;
                    arr[j].y = arr[j+1].y;
                    arr[j+1].x = x1;
                    arr[j+1].y = y1;
            }
            }
        }
    }
}

int distance(Interval a1 , Interval a2){
    if(a1.y > a2.x){
        return (a1.y-a2.x);
    }
    return 0;
}

int small(Interval *arr , int st , int end){
    if(st > end || end == st){
        return 0;
    }else {
        
    }
}

int overlappedInterval(Interval *arr ,int st, int end){
    int size = end - st + 1;
    if(size <= 3){
        return small(arr , st , end);
    }else {

    }
}

int main(){
    int n;
    printf("Enter no of total interval : ");
    scanf("%d",&n);
    Interval *arr = (Interval *) calloc (n , sizeof(Interval)); 
    Interval *arr1 = (Interval *) calloc (n , sizeof(Interval));
    Interval *arr2 = (Interval *) calloc (n , sizeof(Interval));
    for(int i=0 ; i<n ; i++){
        scanf("%d",&arr[i].x);
        scanf("%d",&arr[i].y);
        arr1[i].x = arr[i].x;
        arr1[i].y = arr[i].y;
        arr2[i].x = arr[i].x;
        arr2[i].y = arr[i].y;
    }
    print(arr, n);
    sorting(arr1 , n ,0);
    print(arr1,n);
    sorting(arr2,n,1);
    print(arr2,n);
    return 0;
}