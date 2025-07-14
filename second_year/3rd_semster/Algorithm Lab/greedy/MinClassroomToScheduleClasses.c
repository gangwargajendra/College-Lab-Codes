#include<stdio.h>
#include<stdlib.h>

typedef struct pair Pair;
struct pair{
    int st,end;
};

int compare(const void *a , const void *b){
    Pair *a1 = (Pair *)a;
    Pair *b1 = (Pair *)b;
    return a1->st - b1->st;
}

void print(Pair *arr , int n){
    printf("array : ");
    for(int i=0 ; i<n ; i++){
        printf("(%d , %d) , ",arr[i].st,arr[i].end);
    }
    printf("\n");
}

void heapify(Pair *arr , int n , int i){
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && arr[smallest].end > arr[left].end){
        smallest = left;
    }
    if(right < n && arr[smallest].end > arr[right].end){
        smallest = right;
    }
    if(i != smallest){
        int e = arr[i].end;
        int s = arr[i].st;
        arr[i].end = arr[smallest].end;
        arr[i].st = arr[smallest].st;
        arr[smallest].end = e;
        arr[smallest].st = s;
        heapify(arr,n,smallest);
    }
}

void delete(Pair *arr , int *n , int i){
    arr[i].end = arr[(*n)-1].end;
    arr[i].st = arr[(*n)-1].st;
    --(*n);
    for(int i = ((*n)/2)-1 ; i >= 0 ; i--){
        heapify(arr, *n , i);
    }
}

void add(Pair *arr, Pair a , int *size ){
    arr[(*size)].end = a.end;
    arr[(*size)].st = a.st;
    ++(*size);
    for(int i = ((*size)/2)-1 ; i >= 0 ; i--){
        heapify(arr , *size , i);
    }
}

void modifyheap(Pair *heap , Pair a , int *size){
    heap[0].end = a.end;
    heap[0].st = a.st;
    for(int i = ((*size)/2)-1 ; i >= 0 ; i--){
        heapify(heap , *size , i);
    }
}

void MinClassroomToScheduleClass(Pair *arr , int n , Pair *heap,int *size){
    if(n == 0) return;
    add(heap , arr[0] ,size);
    for(int i = 1 ; i < n ; i++){
        Pair firstEnd = heap[0];
        if(arr[i].st < firstEnd.end){
            add(heap, arr[i],size);
        }else{
            modifyheap(heap ,arr[i] ,size);
        }
    }
}

int main(){
    int n;
    printf("Enter number of interval : ");
    scanf("%d",&n);
    Pair *arr = (Pair *) calloc (n , sizeof(Pair));
    printf("Enter starting and ending time : ");
    for(int i=0 ; i<n ;i++){
        scanf("%d",&arr[i].st);
        scanf("%d",&arr[i].end);
    }
    print(arr , n);
    qsort(arr , n , sizeof(Pair) , compare);
    print(arr, n);

    Pair *heap = (Pair *) calloc (n , sizeof(Pair));
    int heapSize = 0;

    MinClassroomToScheduleClass(arr , n , heap ,&heapSize);
    printf("non overlapping interval : %d",heapSize);

    return 0;
}



// cpp code for time limit exceeded

//class Solution {
// public:
//     int minGroups(vector<vector<int>>& intervals) {
//         priority_queue<int, vector<int>, greater<int>> heap;

//         sort(intervals.begin(),intervals.end());
//         int ans = 1;
//         heap.push(intervals[0][1]);

//         for(int i=1 ; i<intervals.size() ; i++){
//             if(intervals[i][0] <= heap.top()) {
//                 heap.push(intervals[i][1]);
//             }else{
//                 heap.pop();
//                 heap.push(intervals[i][1]);
//             }
//         }
//         return heap.size();
//     }
// };