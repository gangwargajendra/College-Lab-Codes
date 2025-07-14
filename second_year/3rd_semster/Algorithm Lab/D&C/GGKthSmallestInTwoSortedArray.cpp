#include<iostream>
using namespace std;

int findKth(int arr1[] ,int arr2[], int n1, int n2 , int k){
    if(n1 > n2){
        return findKth(arr2 , arr1 ,n2 , n1, k);
    }
    if(n1 == 0){
        return arr2[k-1];
    }
    if(k == 1){
        return min(arr1[0] , arr2[0]);
    }
    
    int i = min(n1 , k / 2);
    int j = k-i;
    if(arr1[i-1] < arr2[j-1]){
        //exclude first i element from arr1
        return findKth(arr1+i , arr2 , n1-i-1 , n2 , k-i);
    }else {
        //exclude first j element from arr2
        return findKth(arr1 , arr2+j , n1 , n2-j-1 , k-j);
    }
}

int findKth(int arr1[] ,int arr2[], int n1, int n2 , int k){
    if(n1 > n2){
        return findKth(arr2 , arr1 ,n2 , n1, k);
    }
    if(n1 == 0){
        return arr2[k-1];
    }
    if(k == 1){
        return min(arr1[0] , arr2[0]);
    }
    
    

    int i = min(n1 , k / 2);
    int j = k-i;
    if(arr1[i-1] < arr2[j-1]){
        //exclude first i element from arr1
        return findKth(arr1+i , arr2 , n1-i-1 , n2 , k-i);
    }else {
        //exclude first j element from arr2
        return findKth(arr1 , arr2+j , n1 , n2-j-1 , k-j);
    }
}

int main(){
    int n1,n2;
    cout << "Enter the size of two array : ";
    cin >> n1 >> n2;
    int arr1[n1] , arr2[n2];
    cout << "Enter " << n1 << " elements of first array : ";
    for(int i=0 ; i<n1 ;i++){
        cin >> arr1[i];
    }
    cout << "Enter " << n2 << " elements of second array : ";
    for(int i=0 ; i<n2 ;i++){
        cin >> arr2[i];
    }
    int k;
    cout <<"Enter number for finding the smallest one : ";
    for(int i = 0 ; i < n1+n2 ; i++){
        int small = findKth(arr1 , arr2 , n1 , n2, i);
        cout << k << "th smallest element : " << small << endl;
    }
    return 0;
}