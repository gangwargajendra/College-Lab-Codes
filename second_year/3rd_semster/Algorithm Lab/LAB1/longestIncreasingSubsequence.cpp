#include<iostream>
#include<cmath>
using namespace std;

int maxSequence(int *arr ,int n){
    int LIS[n];
    for (int i = 0; i < n; i++)
    LIS[i] = 1;

    for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
        if (arr[i] > arr[j] && LIS[i] < LIS[j] + 1)
            LIS[i] = LIS[j] + 1;
    }
    }

    int maxi = 1;
    for (int i = 0; i < n; i++)
    maxi = max(maxi, LIS[i]);

    return maxi;
}

// int se(int *arr ,int n){
//     int LIS[n] = {1};
//     int maxi = 0;
//     int leftPre = -1;
//     for(int i = 0 ; i < n ; i++){
//         for(int j = i ; j >= leftPre ; j--){
//             if(arr[i] > arr[j]){
//                 LIS[j]++;
//                 LIS[i] = max(LIS[i] , LIS[j]);
//             }
//             if(LIS[leftPre] < LIS[i]){
//                 leftPre = i;
//             }
//         }
//     }
//     int i;
//     cout << endl;
//     for(i = 0; i < n -1 ; i++){
//         maxi = max(LIS[i] , LIS[i+1]);
//     }
//     cout << LIS[i];
//     return maxi;
// }

int main(){
    int n;
    cout <<"enter size : ";
    cin >> n ;
    int arr[n];
    cout << "Enter " << n << " elements of array : ";
    for(int i = 0 ; i < n ; i++){
        int t;
        cin >> t;
        arr[i] = t;
    }

    cout << "\nmax increasing subssequence digit : " << maxSequence(arr, n);
    return 0;
}