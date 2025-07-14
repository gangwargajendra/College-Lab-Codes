#include<iostream>
#include<algorithm>
using namespace std;

int medianOfMedian(int arr[], int low , int high );

int partition(int arr[] , int low , int high , int pivot){
    int pivotValue = arr[pivot];
    int i ,start = 0;
    swap(arr[pivot] , arr[high]);
    for(i = low ; i < high ; i++){
        if(arr[i] < pivotValue){
            swap(arr[i] , arr[start]);
            start++;
        }
    }
    swap(arr[i] , arr[start]);
    return start;
}

int select(int arr[] , int low , int high , int k){
    if(low == high){
        return arr[low];
    }
    int pivot = medianOfMedian(arr , low , high );
    int newPivot = partition(arr , low , high , pivot);
    if(k == newPivot){
        return arr[k];
    }else if(k < newPivot){
        return select(arr , low , newPivot-1 , k);
    }else{
        return select(arr , newPivot+1 , high , k);
    }
}

int medianOfMedian(int arr[] , int low , int high ){
    int totalNumber = high - low + 1;
    int totalMedian = (totalNumber + 4) / 5;

    int medians[totalMedian];
    for(int i = 0 ; i < totalMedian ; i++){
        int left = low + i * 5;
        int right = min(left + 4 , high);
        sort(arr+left , arr+right);
        medians[i] = arr[(left + right) / 2];
    }
    if(totalMedian == 1){
        return medians[0];
    }else{
        return select(medians , 0 , totalMedian-1 , totalMedian/2);
    }

}

int findsmallest(int arr[] , int size , int k){
    if(k < 0 || k > size){
        cout << "out of range";
        return -1;
    }else {
        return select(arr , 0 , size , k);
    }
}

int main(){
    int size;
    cout << "Enter size of array : ";
    cin >> size;
    int arr[size];
    cout << "Enter " << size << " elemets of array : ";
    for(int i = 0 ; i < size ; i++){
        cin >> arr[i];
    }
    int k;
    cout << "Enter for smallest element : ";
    cin >> k;
    cout << k << "th smallest element : " << findsmallest(arr , size-1 , k);
    return 0;
}