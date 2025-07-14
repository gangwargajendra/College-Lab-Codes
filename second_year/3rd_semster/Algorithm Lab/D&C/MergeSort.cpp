#include<iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    int i , j;
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSort(int arr[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;

        mergeSort(arr, start , mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
}

int main(){
    int n;
    cout << "Enter the size of array : " ;
    cin >> n;
    int arr[n];
    cout << "Enter " << n << " elements of array : " ;
    for(int i = 0 ; i < n ; i++){
        cin >> arr[i];
    }
    mergeSort(arr , 0 , n-1);
    cout << "Element of array : ";
    for(int i = 0; i < n ; i++){
        cout << arr[i] << " ";
    }
    return 0;
}