#include<iostream>
using namespace std;

int findMax(int *arr , int low ,int high){
    if(low == high){
        return arr[low];
    }
    if(high == low +1){
        return max(arr[low] , arr[high]);
    }
    int mid = (low + high ) / 2;
    int max1 = findMax(arr , low , mid);
    int max2 = findMax(arr , mid+1 , high);
    return max(max1 , max2);
}

void findMaxandMin(int *arr , int low , int high , int *maxi , int *mini){
    if(low == high){
        *mini = arr[low];
        *maxi = arr[high];
        return ;
    }
    if(high == low+1){
        if(arr[low] > arr[high]){
            *maxi = arr[low];
            *mini = arr[high];
        }else {
            *maxi = arr[high];
            *mini = arr[low];
        }
        return ;
    }
    int mid = (low + high ) / 2;
    int Rmin = INT16_MAX , Rmax = INT16_MIN;
    int Lmin = INT16_MAX , Lmax = INT16_MIN;
    findMaxandMin(arr , low , mid , &Lmax ,&Lmin);
    findMaxandMin(arr , mid+1 , high , &Rmax , &Rmin);
    *mini = min(Lmin , Rmin);
    *maxi = max(Lmax ,Rmax);
}

void findMaxandScndmax(int *arr , int low, int high , int *maxi , int *scndmax){
    if(low == high){
        *maxi = arr[low];
        *scndmax = arr[low];
        return;
    }
    if(high == low + 1){
        if(arr[low] > arr[high]){
            *maxi = arr[low];
            *scndmax = arr[high];
        }else{
            *maxi = arr[high];
            *scndmax = arr[low];
        }
        return;
    }
    int mid = (low + high ) / 2;
    int Rmax = INT16_MAX , RscndMax = INT16_MIN;
    int Lmax = INT16_MAX , LscndMax = INT16_MIN;
    findMaxandMin(arr , low , mid , &Lmax ,&LscndMax);
    findMaxandMin(arr , mid+1 , high , &Rmax , &RscndMax);
    if(Rmax > Lmax){
        *maxi = Rmax;
        if(Lmax > RscndMax){
            *scndmax = Lmax;
        }else {
            *scndmax = RscndMax;
        }
    }else{
        *maxi = Lmax;
        if(Rmax > LscndMax){
            *scndmax = Rmax;
        }else{
            *scndmax = LscndMax;
        }
    }
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

    int max1 = findMax(arr , 0 , size-1);
    cout << "maximum is : " << max1  << endl;

    int mini = INT16_MAX , maxi = INT16_MIN;
    findMaxandMin(arr , 0 , size -1 , &maxi , &mini);
    cout << "minimum = " << mini << " & maximum : " << maxi << endl;

    int max3 = INT16_MIN , scndMax = INT16_MIN;
    findMaxandScndmax(arr, 0 , size-1 , &max3 , &scndMax);
    cout << "maximum : " << max3 << " & second maximum : " << scndMax << endl;
}