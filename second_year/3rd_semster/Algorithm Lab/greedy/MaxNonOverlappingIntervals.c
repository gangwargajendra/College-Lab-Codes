#include<stdio.h>
#include<stdlib.h>

typedef struct pair Pair;
struct pair{
    int st,end;
};

// void merge(Pair *arr , int l , int m , int h){
//     int n1 = m-l+1;
//     int n2 = h-m;

//     Pair L[n1];
//     Pair R[n2];
//     int i=0 , j=0 , k=l;
//     while(i < n1){
//         L[i].st = arr[l+i].st;
//         L[i].end = arr[l+i].end;
//         i++;
//     }
//     while(j < n2){
//         R[j].st = arr[m+1+j].st;
//         R[j].end = arr[m+1+j].end;
//         j++;
//     }
//     i = 0 , j = 0;
//     while(i < n1 && j < n2){
//         if(L[i].end < R[j].end){
//             arr[k].st = L[i].st;
//             arr[k].end = L[i].end;
//             i++;
//         }else{
//             arr[k].st = R[j].st;
//             arr[k].end = R[j].end;
//             j++;
//         }
//         k++;
//     }
//     while(i < n1){
//         arr[k].st = L[i].st;
//         arr[k].end = L[i].end;
//         i++ , k++;
//     }
//     while(j < n2){
//         arr[k].st = R[j].st;
//         arr[k].end = R[j].end;
//         k++ , j++;
//     }
// }

// void mergeSort(Pair *arr , int low, int high){
//     if(high > low){
//         int mid = low + (high - low) / 2;
//         mergeSort(arr , low , mid);
//         mergeSort(arr, mid+1 , high);
//         merge(arr , low, mid , high);
//     }
// }

int compare(const void *a , const void *b){
    Pair *a1 = (Pair *)a;
    Pair *b1 = (Pair *)b;
    return a1->end - b1->end;
}

void print(Pair *arr , int n){
    printf("array : ");
    for(int i=0 ; i<n ; i++){
        printf("(%d , %d) , ",arr[i].st,arr[i].end);
    }
    printf("\n");
}

int NonOverlappingIntervals(Pair *arr , int n){
    int maxClass = 1;
    Pair currentClass = arr[0]; 
    for(int i=1 ; i<n ; i++){
        if(arr[i].st >= currentClass.end){
            maxClass++;
            currentClass = arr[i];
        }else{
            continue;
        }
    }
    return maxClass;
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
    // // mergeSort(arr ,0 , n-1);
    qsort(arr , n , sizeof(Pair) , compare);
    print(arr, n);

    int t = NonOverlappingIntervals(arr , n);
    printf("non overlapping interval : %d",t);

    return 0;
}