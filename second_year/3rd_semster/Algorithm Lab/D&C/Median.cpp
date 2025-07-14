#include<iostream>
#include<algorithm>
using namespace std;
int medianForMedian(int arr[] , int left, int right , int k);

int partition(int arr[] , int left , int right , int k){
    if(left == right){
        return arr[left];
    }
    int pivotValue = arr[k];
    int startValue = left;
    for(int i = left ; i < right ; i++){
        if(arr[i] < pivotValue){
            swap(arr[i] , arr[startValue]);
            startValue++;
        }
    }
    swap(arr[startValue] ,arr[right]);
    return startValue;
}

int select(int arr[] , int left , int right , int k){
    if(left == right){
        return arr[left];
    }
    int pivot = medianForMedian(arr , left , right , k);
    int newPivot = partition(arr ,left , right , pivot);
}

int medianForMedian(int arr[] , int left , int right, int k){
    int numNumbers = right - left + 1;
    int numMedians = (numNumbers + 4) / 5;
    int *medians = new int[numMedians];
    for(int i = 0 ; i < numMedians ; i++){
        int low = left + i * 5;
        int high = min(low + 4 , right);
        sort(arr + low , arr + high +1);
    }
}


int findMedian(int arr[] , int left , int right, int k){
    if(left > right){
        cout << "array is empty ";
    }else if(left == right){
        return arr[left];
    }
    return select(arr , left , right , k);
}

int main(){
    int size;
    cout << "Enter size of array : ";
    cin >> size;
    int arr[size];
    cout << "Enter " << size << " elements of array : ";
    for(int i = 0 ; i < size ; i++){
        cin >> arr[i];
    }
    int k = size / 2;

    cout << "median : " << findMedian(arr , 0 , size -1 , k);
    return 0;
}