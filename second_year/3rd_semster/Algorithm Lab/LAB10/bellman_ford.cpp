// gfg - Distance from the source(Bellman-ford algorithm)
//bellman ford algorithm to compute shortest path 
// it's also works in negative edges
// by this we can detect negative cycles

#include<iostream>
#include<vector>
#include<climits>
using namespace std;

vector<int> bellman_ford(int n, vector<vector<int>>& edges, int src) {
    vector<int> dis(n , INT_MAX);
    dis[src] = 0;
    // time complexity = V * E = vertex * edges
    int iteration = 0;
    // iteration is going to n because in last iteration
    // dis vector changes then we say that there is negative cycle
    while(iteration != n-1){
        for(auto it : edges){
            int u = it[0];
            int v = it[1];
            int w = it[2];
            
            if(dis[u] != INT_MAX && dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
            }
        }
        iteration++;
    }
    // Nth iteration to check wether there is a cycle or not
    for(auto it : edges){
        int u = it[0];
        int v = it[1];
        int w = it[2];

        if(dis[u] != INT_MAX && dis[u] + w < dis[v]){
            return {-1};
        }
    }

    // if node is not reachable then put 10^8
    for(int i=0 ; i<n ; i++){
        if(dis[i] == INT_MAX){
            dis[i] = 1e8;
        }
    }
    return dis;
}

int main(){
    int n , m;
    cout << "Enter number of vertex and edges : ";
    cin >> n >> m;

    vector<vector<int>> edges;
    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x , y , w;
        cin >> x >> y >> w;
        edges.push_back({x, y , w});
    }

    for(int i=0 ; i<m ; i++){
        cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << "   ";
    }
    cout << endl;

    int src;
    cout << "Enter source : ";
    cin >> src;

    vector<int> ans = bellman_ford(n , edges , src);

    cout << "distance vector : ";
    for(auto it : ans){
        cout << it << " ";
    }
    return 0;
}