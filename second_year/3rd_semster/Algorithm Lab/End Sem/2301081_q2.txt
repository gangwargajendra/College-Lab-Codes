#include<bits/stdc++.h>
using namespace std;

int f(int i , int j,string s1 ,string s2 ,vector<int> costA, vector<int> &costB, vector<vector<int>> &DP){
    if(i == -1){
        int sum = 0;
        for(int k=0 ; k<=j ; k++){
            sum += costB[k];
        }
        return sum;
    }
    if(j == -1){
        int sum = 0;
        for(int k=0 ; k<=i ; k++){
            sum += costA[k];
        }
        return sum;
    }

    if(DP[i][j] != -1) return DP[i][j];

    int equal = 1e9, notEqual = 1e9;
    if(s1[i] == s2[j]){
        equal = min({0 + f(i-1 , j-1 ,s1, s2 ,costA,costB ,DP) , 
                       costA[i] +  f(i-1 ,j , s1, s2, costA ,costB ,DP),
                       costB[j] + f(i , j-1 , s1, s2, costA , costB ,DP)});
    }else{
        notEqual = min({costA[i] + f(i-1 ,j ,s1,s2,costA ,costB ,DP),
                        costB[j] + f(i , j-1 ,s1,s2,costA , costB , DP)});
    }

    return DP[i][j] = min(equal , notEqual);
}

int minDeletionCost(string s1 ,string s2 ,vector<int> &costA, vector<int> &costB){
    int l1 = s1.size();
    int l2 = s2.size();

    vector<vector<int>> DP(l1 , vector<int>(l2 , -1));

    return f(l1-1 , l2-1 , s1,s2,costA ,costB ,DP);
}

int main(){
    string s1 , s2;
    cout << "Enter first string : ";
    cin >> s1;
    cout << "if want to make second string empty then enter '1' otherwise '0' : ";
    int f;
    cin >> f;
    if(f){
        s2 = "";
    }else{
        cout << "Enter second string : ";
        cin >> s2;
    }

    int l1 = s1.size();
    int l2 = s2.size();

    vector<int> costA(l1);
    vector<int> costB(l2);

    cout << "Enter first string deletion cost : ";
    for(int i=0 ; i<l1 ; i++){
        cin >> costA[i];
    }

    cout << "Enter second string deletion cost : ";
    for(int i=0 ; i<l2 ; i++){
        cin >> costB[i];
    }

    cout << "\nminimum cost : " << minDeletionCost(s1 ,s2 ,costA ,costB);

    return 0;
}