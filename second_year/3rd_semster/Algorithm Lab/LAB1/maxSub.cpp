#include<iostream>
using namespace std;

int maxSubarraySum(int *arr, int n){
    int currentSum = 0;
    int maxSum = INT8_MIN;
    for(int i = 0; i < n ; i++){
        currentSum += arr[i];
        maxSum = max(maxSum ,currentSum);
        if(currentSum < 0){
            currentSum = 0;
        }
    }
    cout << maxSum << endl;
    return maxSum;
}

int main(){
    int n;
    cout<<"Enter size of array : ";
    cin >> n;
    int arr[n];

    cout << "Enter " << n << " elements of array : ";
    for(int i = 0; i < n ; i++){
        cin >> arr[i];
    }

    int maxSum = maxSubarraySum(arr, n);
    cout << "maximum sum of an subarray : " << maxSum << endl;
    return 0;
}