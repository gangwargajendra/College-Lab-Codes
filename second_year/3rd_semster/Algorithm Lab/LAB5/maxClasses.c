#include<stdio.h>
#include<stdlib.h>

typedef struct pair Pair;
struct pair{
    int st;
    int end;
};

// void merge(Pair *arr, int l, int m, int r) {
//     int i, j, k;
//     int n1 = m - l + 1;
//     int n2 = r - m;

//     Pair L[n1], R[n2];

//     for (i = 0; i < n1; i++){
//         L[i].end = arr[l + i].end;
//         L[i].st = arr[l + i].st;
//     }
//     for (j = 0; j < n2; j++){
//         R[j].end = arr[m + 1 + j].end;
//         R[j].st = arr[m + 1 + j].st;
//     }
//     i = 0;
//     j = 0; 
//     k = l; 
//     while (i < n1 && j < n2) {
//         if (L[i].end <= R[j].end) {
//             arr[k].end = L[i].end;
//             arr[k].st = L[i].st;
//             i++;
//         } else {
//             arr[k].end = R[j].end;
//             arr[k].st = R[j].st;
//             j++;
//         }
//         k++;
//     }
//     while (i < n1) {
//         arr[k].end = L[i].end;
//         arr[k].st = L[i].st;
//         i++;
//         k++;
//     }
//     while (j < n2) {
//         arr[k].end = R[j].end;
//         arr[k].st = R[j].st;
//         j++;
//         k++;
//     }
// }

// void mergeSort(Pair *arr, int l, int r) {
//     if (l < r) {
//         int m = l + (r - l) / 2;
//         mergeSort(arr, l, m);
//         mergeSort(arr, m + 1, r);
//         merge(arr, l, m, r);
//     }
// }

int compare(const void *a , const void *b){
    Pair *a1 = (Pair *)a;
    Pair *b1 = (Pair *)b;
    return a1->end - b1->end;
}

int maximumClass(Pair *arr , int n){
    if(n == 0){
        return 0;
    }
    int maxClass = 1;
    Pair currentclass = arr[0];
    for(int i = 1 ; i < n ; i++){
        if(arr[i].st >= currentclass.end){
            currentclass = arr[i];
            maxClass++;
        }
    }
    return maxClass;
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

    print(arr, n);
    // mergeSort(arr, 0, n-1);
    qsort(arr , n , sizeof(arr[0]), compare);
    print(arr, n);

    int maxClass = maximumClass(arr , n);
    printf("maximum class that can happen in one class room : %d",maxClass);

    return 0;
}