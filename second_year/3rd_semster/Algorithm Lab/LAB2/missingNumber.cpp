#include<iostream>
using namespace std;

int findMissingNumber(int *arr , int low , int high){
    if(low == high){
        if(arr[low] != low + 1){
            return (low +1);
        }
    }else if(low > high){
        return high + 2;
    }
    int mid = (low + high ) / 2;
    if(arr[mid] > mid +1){
        return findMissingNumber(arr ,low ,mid );
    }else {
        return findMissingNumber(arr , mid+1 , high);
    }
    return -1;
}

int main(){
    int size;
    cout << "Enter the size of array : ";
    cin >> size;
    int arr[size];
    cout << "Enter " << size << " elements of array : ";
    for(int i= 0 ; i < size ; i++){
        cin >> arr[i];
    }
    int num = findMissingNumber(arr , 0 , size-1);
    cout << "missing  number : " << num << endl;
}