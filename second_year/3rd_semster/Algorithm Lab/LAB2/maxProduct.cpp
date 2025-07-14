#include<iostream>
#include<vector>
#include <climits>
using namespace std;

// int crossProduct(vector<int> &arr , int low, int mid , int high){
//     int currentPro = 1;
//     int LminPro = arr[mid];
//     int LmaxPro = arr[mid];
//     for(int i =  mid ; i >= 0 ; i--){
//         currentPro *= arr[i];
//         LmaxPro = max(currentPro , LmaxPro);
//         LminPro = min(currentPro , LminPro);
//     }
//     currentPro = 1;
//     int RmaxPro = arr[mid+1], RminPro = arr[mid+1];
//     for(int i = mid+1 ; i < high ; i++){
//         currentPro *= arr[i];
//         RmaxPro = max(currentPro , RmaxPro);
//         RminPro = min(currentPro , RminPro);
//     }
//     return max((LmaxPro * RmaxPro) , (LminPro * RminPro));
// }

int findMaxProduct(vector<int> &arr, int low, int high) {
    if (low == high) return arr[low];

    int mid = (low + high) / 2;

    // Left product
    int leftMax = findMaxProduct(arr, low, mid);
    // Right product
    int rightMax = findMaxProduct(arr, mid + 1, high);

    // Cross product
    int leftProd = 1, maxLeftProd = INT_MIN, minLeftProd = INT_MAX;
    for (int i = mid; i >= low; i--) {
        leftProd *= arr[i];
        maxLeftProd = max(maxLeftProd, leftProd);
        minLeftProd = min(minLeftProd, leftProd);
        if (arr[i] == 0) leftProd = 1; // reset for zero
    }

    int rightProd = 1, maxRightProd = INT_MIN, minRightProd = INT_MAX;
    for (int i = mid + 1; i <= high; i++) {
        rightProd *= arr[i];
        maxRightProd = max(maxRightProd, rightProd);
        minRightProd = min(minRightProd, rightProd);
        if (arr[i] == 0) rightProd = 1; // reset for zero
    }

    int crossMax = max(
        maxLeftProd * maxRightProd,
        max(minLeftProd * minRightProd,
        max(maxLeftProd * minRightProd,
        minLeftProd * maxRightProd
        )));

    return max(leftMax, max(rightMax, crossMax));
}

// int findMaxProduct(vector<int> &arr , int low , int high){
//     if(low < high){
//         int mid = low + (high - low) / 2;
//         int Lpro = findMaxProduct(arr, low , mid);
//         int Rpro = findMaxProduct(arr , mid+1 , high);
        
//         int middlePro = crossProduct(arr , low , mid , high);

//         return max(Lpro , max(Rpro , middlePro));
//     }else{
//         return arr[low];
//     }
// }

int main(){
    int size;
    cout<< "Enter the size of array : ";
    cin >> size;
    vector<int> arr(size);
    cout << "Enter " << size << " elements of array : ";
    for(int i = 0 ; i < size ; i++){
        cin >> arr[i];
    }
    int maxPro = findMaxProduct(arr , 0 , size - 1);
    cout << "maximum product : "<< maxPro << endl;
}

