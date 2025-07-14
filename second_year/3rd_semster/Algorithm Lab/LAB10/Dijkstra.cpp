#include<bits/stdc++.h>
using namespace std;

vector<int> shortestPath(vector<vector<pair<int,int>>> &adj , int n,int src){
    if(n == 0) return {};

    priority_queue<pair<int,int>, vector<pair<int,int>> ,greater<pair<int,int>>> pq;
    vector<int> dis(n , INT_MAX);

    dis[src] = 0;
    pq.push({0 , src});

    while(!pq.empty()){
        int dist = pq.top().first;
        int crnt = pq.top().second;
        pq.pop();

        for(auto it : adj[crnt]){
            int weight = it.second;
            int neigh = it.first;
            if(dis[neigh] > dist + weight){
                dis[neigh] = dist + weight;
                pq.push({dis[neigh] , neigh});
            }
        }
    }

    return dis;
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

    int src;
    cout << "Enter source : ";
    cin >> src;

    vector<int> ans = shortestPath(adj , n,src);

    for(int i=0 ; i<ans.size() ; i++){
        cout << ans[i] << " ";
    }

    return 0;
}