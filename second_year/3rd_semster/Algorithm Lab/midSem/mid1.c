#include<stdio.h>
#include<stdlib.h>

typedef struct interval Interval;
struct interval{
    int st,end;
};


int compare(const void *a , const void *b){
    Interval *a1 = (Interval *)a;
    Interval *b1 = (Interval *)b;
    return a1->st - b1->st;
}

void print(Interval *arr , int n){
    printf("Intervals : ");
    for(int i=0 ; i<n ; i++){
        printf("(%d , %d) , ",arr[i].st,arr[i].end);
    }
    printf("\n");
}


int binary(int *arr , int st , int end , int target){
    if(st < end){
        int mid = (st+end)/2;
        if(arr[mid] == target){
            return target;
        }
        if(arr[mid] < target && arr[mid+1] > target){
            return arr[mid];
        }
        if(arr[mid] > target){
            return binary(arr , st , mid , target);
        }else{
            return binary(arr ,mid+1 , end , target);
        }
    }
} 

// int binary(int *arr , int n , int target){
//     for(int i=n-1 ; i>=0 ; i--){
//         if(arr[i] == target){
//             return arr[i];
//         }else if(arr[i] < target){
//             return arr[i];
//         }
//     }
//     return -1;
// }


int minPoints(Interval *arr, int n ,int *point , int p , int *po){
    int points = 0;
    int maxPoint = binary(point , 0 , p-1 , arr[0].end);
    po[points] = maxPoint;
    points++;
    for(int i=1 ; i<n ; i++){
        if(maxPoint >= arr[i].st){
            if(maxPoint <= arr[i].end){
                continue;
            }else{
                po[points-1] = binary(point , 0,p-1 , arr[i].end);
            }
        }else{
            maxPoint = binary(point , 0,p-1 , arr[i].end);
            po[points] = maxPoint;
            points++;
        }
    }
    return points;
}

int main(){
    int n;
    printf("Enter number of interval : ");
    scanf("%d",&n);
    Interval *arr = (Interval *) calloc (n , sizeof(Interval));
    printf("Enter starting and ending time : ");
    for(int i=0 ; i<n ;i++){
        scanf("%d",&arr[i].st);
        scanf("%d",&arr[i].end);
    }

    int p;
    printf("Enter number of points : ");
    scanf("%d",&p);
    int point[p];
    printf("Enter points : ");
    for(int i=0 ;i<p ; i++){
        scanf("%d",&point[i]);
    }
    print(arr , n);
    // // mergeSort(arr ,0 , n-1);
    qsort(arr , n , sizeof(Interval) , compare);
    print(arr, n);

    int *po = (int *) calloc(p , sizeof(int));
    int t = minPoints(arr , n , point ,p , po);
    printf("minimum points : %d\n",t);
    printf("elemets : ");
    for(int i=0 ; i<t ;i++){
        printf("%d ",po[i]);
    }

    return 0;
}