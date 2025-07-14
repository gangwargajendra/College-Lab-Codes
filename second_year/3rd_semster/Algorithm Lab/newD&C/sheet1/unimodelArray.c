#include<stdio.h>

int max(int a, int b){
    return a> b ? a : b;
}

int small(int a , int b , int c){
    if(a > b && b > c){
        return a;
    }else if(a < b && b > c){
        return b;
    }else if(a < b && b < c){
        return c;
    }
    return -1;
}

int findPeak(int *a , int st , int end){
    if(st < end){
        if(st+1 == end){
            return max(a[st] , a[end]);
        }
        if(st+2 == end){
            return small(a[st] , a[st+1] , a[end]);
        }
        int mid = (st + end) / 2;
        if(a[mid] < a[mid+1]){
            return findPeak(a ,mid+1 , end);
        }else{
            return findPeak(a , st , mid);
        }
    }
}

int main(){
    int n;
    printf("Enter size : ");
    scanf("%d",&n);
    int a[n];
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]);
    }

    int peak = findPeak(a , 0 , n-1);
    printf("peak = %d",peak);
    return 0;
}