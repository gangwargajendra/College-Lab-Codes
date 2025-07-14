#include<stdio.h>
#include<stdlib.h>

void heapfy(int *arr , int n, int i){
    int greatest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < n && arr[greatest] < arr[left]){
        greatest = left;
    }

    if(right < n && arr[greatest] < arr[right]){
        greatest = right;
    }

    if(i != greatest){
        int t = arr[greatest];
        arr[greatest] = arr[i];
        arr[i] = t;
        heapfy(arr, n , greatest);
    }
}

int delete(int *arr , int *size){
    arr[0] = arr[(*size)-1];
    *size -= 1;
    for(int i=(*size)/2 ; i>= 0 ; i--){
        heapfy(arr ,*size , i);
    }
}

void makeHeap(int *arr , int size){
    for(int i=size/2 ; i>=0 ; i--){
        heapfy(arr , size , i);
    }
}

int processingTime(int *currentProcessing , int time){
    int total = time *(currentProcessing[1]+1) + currentProcessing[0];
    return total;
}

int minTimeForKPro(int *arr , int n , int p , int **pro){
    if(n == 0 || p == 0){
        return 0;
    }
    int t = n;
    makeHeap(arr , n);
    for(int i=0 ; i<t ; i++){
        int max = arr[0];
        int t=0;
        int minPro = processingTime(pro[0] , max); 
        for(int j=1 ; j<p ; j++){
            if(minPro > processingTime(pro[j] , max)){
                t = j;
            }
        }
        pro[t][0] = processingTime(pro[t] , max);
        pro[t][1] += 1;
        delete(arr , &n);
    }
    int maxTime = 0;
    for(int i=0 ; i<p ; i++){
        if(maxTime < pro[i][0]){
            maxTime = pro[i][0];
        }
    }
    return maxTime;
}

int main(){
    int n , p;
    printf("Enter total no of jobs an total no of processor : ");
    scanf("%d %d",&n,&p);

    int **pro = (int **) calloc (p , sizeof(int*));
    int *arr = (int *) calloc (n , sizeof(int));
    for(int i=0 ; i<n ; i++){
        scanf("%d",&arr[i]);
    }
    for(int i=0 ; i<p ;i++){
        pro[i] = (int *) calloc (2 , sizeof(int));
    }

    int t = minTimeForKPro(arr , n , p , pro);
    printf("minimum  time to do all jobs with %d processor : %d",p,t);
    return 0;
}