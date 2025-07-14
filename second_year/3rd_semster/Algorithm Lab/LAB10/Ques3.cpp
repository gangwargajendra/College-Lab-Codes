#include<bits/stdc++.h>
using namespace std;

int shortestPair(vector<vector<pair<int,int>>> &adj, int v){
    pair<int,int> ans;
    int mini = INT_MAX;
    for(int i=0 ; i<v ; i++){
        for(auto it : adj[i]){
            if(mini > it.second){
                ans.first = i;
                ans.second = it.first;
                mini = it.second;
            }
        }
    }

    cout << "closest node : " << ans.first << " , " << ans.second << endl;
    return mini;
}

int main(){
    int n,m;
    cout << "Enter total vertex and edges : ";
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n , vector<pair<int,int>>());
    cout << "Enter all edges end weights : ";
    for(int i=0 ; i<m ; i++){
        int x , y  ,w;
        cin >> x >> y >> w;
        adj[x].push_back({y , w});
    }

    int ans = shortestPair(adj , n);

    cout << "Shortest pair : " << ans;

    return 0;
}