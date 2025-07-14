#include<stdio.h>
#include<stdlib.h>

typedef struct pair Pair;
struct pair{
    int st;
    int end;
};

void merge(Pair *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Pair L[n1], R[n2];

    for (i = 0; i < n1; i++){
        L[i].end = arr[l + i].end;
        L[i].st = arr[l + i].st;
    }
    for (j = 0; j < n2; j++){
        R[j].end = arr[m + 1 + j].end;
        R[j].st = arr[m + 1 + j].st;
    }
    i = 0;
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].st <= R[j].st) {
            arr[k].end = L[i].end;
            arr[k].st = L[i].st;
            i++;
        } else {
            arr[k].end = R[j].end;
            arr[k].st = R[j].st;
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k].end = L[i].end;
        arr[k].st = L[i].st;
        i++;
        k++;
    }
    while (j < n2) {
        arr[k].end = R[j].end;
        arr[k].st = R[j].st;
        j++;
        k++;
    }
}

void mergeSort(Pair *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(Pair *arr, int n, int i) {
    int smallest = i; 
    int left = 2 * i + 1;   
    int right = 2 * i + 2;    

    if (left < n && arr[left].end < arr[smallest].end)
        smallest = left;

    if (right < n && arr[right].end < arr[smallest].end)
        smallest = right;

    if (smallest != i) {
        int start = arr[i].st;
        int en = arr[i].end;
        arr[i].end = arr[smallest].end;
        arr[i].st = arr[smallest].st;
        arr[smallest].end = en;
        arr[smallest].st = start;
        heapify(arr, n, smallest);
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

void maximumClassRoom(Pair *arr , int n , Pair *heap,int *size){
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

void print(Pair *arr ,int n){
    printf("Classes timeing : ");
    for(int i=0 ; i<n ; i++){
        printf("(%d , %d), ",arr[i].st,arr[i].end);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter no of classes : ");
    scanf("%d",&n);
    Pair *arr =(Pair *) calloc(n , sizeof(struct pair)); 
    for(int i=0 ; i<n ;i++){
        printf("Enter %dth class starting and ending time : ",i+1);
        scanf("%d",&arr[i].st);
        scanf("%d",&arr[i].end);
    }

    Pair *heap =(Pair *) calloc(n , sizeof(struct pair));

    print(arr, n);
    mergeSort(arr, 0, n-1);
    print(arr, n);

    int size = 0;
    maximumClassRoom(arr , n , heap, &size);
    printf("maximum rooms required to happen all classes : %d",size);

    return 0;
}