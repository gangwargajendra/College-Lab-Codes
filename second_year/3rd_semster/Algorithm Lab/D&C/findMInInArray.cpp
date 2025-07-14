#include<iostream>
using namespace std;

int findMin(int *arr, int start , int end){   // with time complxty= O(logn)
    if(start == end){
        return arr[start];
    }else {
        int mid = start + (end - start) / 2;
        return min(findMin(arr , start , mid) , findMin(arr , mid+1 , end));
    }
}

void MinAndMax(int *arr ,int start , int end , int *mini , int *maxi){
    if(start == end){
        *mini = arr[start];
        *maxi = arr[start];
        return;
    }
    if(end == start + 1){
        *mini = min(arr[end] , arr[start]);
        *maxi = max(arr[start] , arr[end]);
        return;
    }

    int mid = (start + end) / 2;
    int left_min = INT16_MAX , left_max = INT16_MIN;
    int right_min = INT16_MAX , right_max = INT16_MIN;

    MinAndMax(arr, start , mid , &left_min , &left_max);
    MinAndMax(arr, mid +1 , end , &right_min , &right_max);
    
    *mini = min(left_min , right_min);
    *maxi = max(left_max , right_max);
}

void MaxandSecondMax(int *arr ,int start ,int end , int *maxi , int *scndMax){
    if(start == end){
        *maxi = arr[start];
        *scndMax = arr[start];
        return;
    }
    if(end == start + 1){
        if(arr[start] > arr[end]){
            *maxi = arr[start];
            *scndMax = arr[end];
        }else{
            *maxi = arr[end];
            *scndMax = arr[start];
        }
        return ;
    }
    int mid = (start + end) / 2;
    int L_max = INT16_MIN , L_smax = INT16_MAX;
    int R_max = INT16_MIN , R_smax = INT16_MAX;

    MaxandSecondMax(arr , start , mid , &L_max , &L_smax);
    MaxandSecondMax(arr ,mid +1 , end , &R_max , &R_smax);

    if(L_max > R_max){
        *maxi = L_max;
        if(R_max > L_smax){
            *scndMax = R_max;
        }else{
            *scndMax = L_smax;
        }
    }else {
        *maxi = R_max;
        if(L_max > R_smax){
            *scndMax = L_max;
        }else{
            *scndMax = R_smax;
        }
    }
}

int BinarySearch(int *arr , int start , int end , int target){
    if(start <= end){
        int mid = (start + end ) / 2 ;
        if(arr[mid] == target){
            return mid;
        }else if(target > arr[mid]){
            return BinarySearch(arr , mid+1 , end , target);
        }else if(target < arr[mid]){
            return BinarySearch(arr , start , mid , target);
        }
    }
    return -1;
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

    // int minimum = findMin(arr , 0 , n - 1);
    // cout << "minimum of array : " << minimum << endl;
    // int mini = INT16_MAX , maxi = INT16_MIN;
    // MinAndMax(arr , 0 , n-1 , &mini , &maxi);
    // cout << "minimum = " << mini << " & maximum : " << maxi << endl;

    // int maxi = INT16_MIN , scndMax = INT16_MIN;
    // MaxandSecondMax(arr , 0 , n-1 , &maxi , &scndMax); 
    // cout << "max : " << maxi << " & second max : " << scndMax << endl;

    int target;
    cout << "enter target value : ";
    cin >> target;
    cout << "index = " << BinarySearch(arr , 0 , n-1 , target);
    return 0;
}