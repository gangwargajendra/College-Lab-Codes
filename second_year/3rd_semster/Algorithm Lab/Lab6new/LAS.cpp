// longest alternating subsequence(LAS)
#include<iostream>
#include<vector>
using namespace std;

int LAS(int n,vector<int> &sequence){
    vector<int> up(n ,1);
    vector<int> down(n,1);
    for(int i=1 ; i<n ; i++){
        if(sequence[i] > sequence[i-1]){
            up[i] = 1 + down[i-1];
            down[i] = down[i-1];
        }else if(sequence[i] < sequence[i-1]){
            down[i] = 1 + up[i-1];
            up[i] = up[i-1];
        }else{
            down[i] = down[i-1];
            up[i] = up[i-1];
        }
    }
    return max(up[n-1],down[n-1]);
}

int main(){
    int n;
    cout << "Enter number of element : ";
    cin >> n;

    vector<int> sequence(n);
    cout << "Enter all elements : ";
    for(int i=0 ; i<n ; i++){
        cin >> sequence[i];
    }

    int m = LAS(n , sequence);

    cout << "longest alternating subsequence : " << m;

    return 0;
}

