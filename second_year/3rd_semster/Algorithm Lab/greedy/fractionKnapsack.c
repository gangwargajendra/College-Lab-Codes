#include<stdio.h>
#include<stdlib.h>

typedef struct item Item;
struct item{
    int value;
    int weight;
    float fraction;
};

void merge(Item *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Item L[n1], R[n2];

    for (i = 0; i < n1; i++){
        L[i].value = arr[l + i].value;
        L[i].weight = arr[l + i].weight;
        L[i].fraction = arr[l+i].fraction;
    }
    for (j = 0; j < n2; j++){
        R[j].value = arr[m + 1 + j].value;
        R[j].weight = arr[m + 1 + j].weight;
        R[j].fraction = arr[m + 1 + j].fraction;
    }
    i = 0;
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].fraction <= R[j].fraction) {
            arr[k].value = L[i].value;
            arr[k].fraction = L[i].fraction;
            arr[k].weight = L[i].weight;
            i++;
        } else {
            arr[k].value = R[j].value;
            arr[k].fraction = R[j].fraction;
            arr[k].weight = R[j].weight;
            j++;
        }
        k++;
    }
    while (i < n1) {
            arr[k].value = L[i].value;
            arr[k].fraction = L[i].fraction;
            arr[k].weight = L[i].weight;        i++;
        k++;
    }
    while (j < n2) {
            arr[k].value = R[j].value;
            arr[k].fraction = R[j].fraction;
            arr[k].weight = R[j].weight;
        j++;
        k++;
    }
}

void mergeSort(Item *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


void print(Item *arr , int n){
    printf("Items : \n");
    for(int i=0 ; i<n ; i++){
        printf("item %d : va = %d, we = %d,frac = %f\n",i+1,arr[i].value,arr[i].weight,arr[i].fraction);
    }
    printf("\n");
}

int maxValue(Item *arr , int n, int total){
    int maxValue = 0;
    for(int i=0 ; i< n ; i++){
        if(total >= arr[i].weight){
            maxValue += arr[i].value;
            total = total - arr[i].weight;
        }else if(total > 0) {
            maxValue += arr[i].fraction * total;
            total = -1;
        }else{
            break;
        }
    }
    return maxValue;
}

int main(){
    int n;
    printf("Enter total no of items : ");
    scanf("%d",&n);

    Item *arr = (Item *) calloc (n , sizeof(Item));
    printf("Enter items value and weight : ");
    for(int i=0 ; i<n ; i++){
        int t , m;
        scanf("%d",&t);
        scanf("%d",&m);
        arr[i].value = t;
        arr[i].weight = m;
        arr[i].fraction = (float)t/(float)m;
    }

    print(arr, n);
    mergeSort(arr,0 , n-1);
    print(arr, n);

    int totalWeight;
    printf("Enter total weight : ");
    scanf("%d",totalWeight);

    int max = maxValue(arr , n , totalWeight);
    printf("maximum value : %d",max);
    return 0;
}