// prim algorithm

#include<bits/stdc++.h>
using namespace std ;

vector<pair<int,int>> MST(vector<vector<pair<int,int>>> &adj , int n){
    if(n == 0) return {};

    priority_queue<pair<int,pair<int,int>> , vector<pair<int,pair<int,int>>> , greater<pair<int,pair<int,int>>>> pq;

    pq.push({0 , {0 , -1}}); // weight , node, parent
    vector<int> vis( n , 0);
    vector<pair<int,int>> ans;
    int mstWeight = 0;

    while(!pq.empty()){
        int weight = pq.top().first;
        int crnt = pq.top().second.first;
        int prnt = pq.top().second.second;
        pq.pop();

        if(prnt != -1 && !vis[crnt]){
            ans.push_back({crnt,prnt});
            mstWeight += weight;
        }else if(vis[crnt]){
            continue;
        }

        vis[crnt] = 1;

        for(auto it : adj[crnt]){
            int weightNeigh = it.second;
            int neigh = it.first;
            if(!vis[neigh]){
                pq.push({weightNeigh , {neigh , crnt}});
            }
        }   
    }

    cout << "MST weight : " << mstWeight << endl;
    return ans;
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
        adj[y].push_back({x , w});
    }

    vector<pair<int,int>> ans = MST(adj , n);

    for(int i=0 ; i<ans.size() ; i++){
        cout << "(" << ans[i].first << "," << ans[i].second << "),";
    }

    return 0;
}