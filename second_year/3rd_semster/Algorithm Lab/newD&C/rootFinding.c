#include<stdio.h>
#include<stdlib.h>

int computeValue(int *arr , int x){
    int value = arr[0] + arr[1] * x + arr[2] * x * x;
    return value;
}

int findRoot(int *arr , int st , int end){
    if(st <= end){
        int midPoint = (st + end) / 2;
        if(computeValue(arr, midPoint) == 0){
            return midPoint;
        }else if(st == end){
            return -1;
        }
        int leftPoint = findRoot(arr,st , midPoint);
        int rightPoint = findRoot(arr, midPoint+1 , end);
        if(leftPoint >= st && leftPoint <= end){
            return leftPoint;
        }else if(rightPoint >= st && rightPoint <= end){
            return rightPoint;
        }else {
            return -1;
        }
    }else{
        return -1;
    }
}

int main(){
    int arr[3];
    for(int i=0 ; i<3 ; i++){
        printf("Enter coefficient of x^%d : ",i);
        scanf("%d",&arr[i]);
    }

    int n;
    printf("Enter number which will greater than root : ");
    scanf("%d",&n);

    int root = findRoot(arr ,0 ,n);
    printf("root is : %d",root);
    return 0;
}