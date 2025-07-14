#include<iostream>
#include<vector>
using namespace std;

int LPS(int i , int j ,vector<int> &sequence,vector<vector<int>> &memo){
    if(i > j){
        return 0;
    }

    if(memo[i][j] != -1){
        return memo[i][j];
    }

    if(sequence[i] == sequence[j]){
        memo[i][j] = 2 + LPS(i+1 , j-1 , sequence , memo);
    }else{
        memo[i][j] = max(LPS(i+1 , j , sequence,memo) , LPS(i , j-1,sequence,memo));
    }

    return memo[i][j];
}

int main(){
    int n;
    cout << "Enter number of element in sequence : ";
    cin >> n;

    vector<int> sequence(n);
    cout << "Enter the elements : ";
    for(int i=0 ; i<n ; i++){
        cin >> sequence[i];
    }

    vector<vector<int>> memo(n , vector<int>(n,-1));
    for(int i=0 ; i<n ; i++){
        memo[i][i] = 1;
    }

    int m = LPS(0,n-1 , sequence , memo);

    cout << "longest palindrone subsequence : " << m;
    return 0;
}