#include<iostream>
using namespace std;

int computePower(int num , int pow){
    if(pow == 0){
        return 1;
    }else if(pow == 1){
        return num;
    }else if(pow == 2){
        return (num * num);
    }
    if(pow % 2 == 0){
        int mid = pow / 2;
        int result = computePower(num , mid);
        return (result * result);
    }else {
        int mid = pow / 2;
        int result = computePower(num , mid);
        return (result * result * num);
    }
    return 0;
}

int main(){
    int num , pow;
    cout << "Enter number and power  : ";
    cin >> num >> pow;

    cout << "power : " << computePower(num , pow);
    return 0;
}