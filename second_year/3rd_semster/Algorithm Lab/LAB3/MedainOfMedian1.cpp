#include<iostream>
#include<algorithm>
using namespace std;

int medianOfMedian(int arr[] , int low , int high);

int partition(int arr[] , int low , int high , int pivot){
    int pivotValue = arr[pivot];
    swap(arr[pivot] , arr[high]);
    int i ,start = 0;
    for(i = low ; i < high ; i++){
        if(arr[i] < pivot){
            swap(arr[i] , arr[start]);
            start++;
        }
    }
    swap(arr[start] , arr[high]);
    return start;
}

int select(int arr[] , int low , int high , int k){
    if(low == high){
        return arr[low];
    }
    int pivot = medianOfMedian(arr , low , high);
    int newPivot = partition(arr , low , high , pivot);

    if(k == newPivot){
        return arr[k];
    }else if(k < newPivot){
        return select(arr , low ,newPivot-1 , k);
    }else{
        return select(arr , newPivot , high , k);
    }
}

int medianForMedian(int arr[] , int high , int low){
    int totalNumber = high - low +1;
    int totalMedian = (totalNumber + 4) / 5;
    int median[totalMedian];
    for(int i = 0 ; i < totalMedian ; i++){
        
    }
}

int find(int *arr , int size , int k){
    if( k < 0 || k > size){
        cout << "invalid...";
    }else{
        return select(arr, 0 , size , k);
    }
}

int main(){
    int arr[] = {5 ,1 ,0 ,4 ,2};
    int size = sizeof(arr) / sizeof(int);

    cout << "small : " << find( arr, size-1 , 2); 
}
