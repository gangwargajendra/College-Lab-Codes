#include<bits/stdc++.h>
using namespace std;

void printAdjList(vector<vector<int>> &adj){
    cout << "\nAdjacency list : \n";
    for(int i=0 ; i<adj.size() ; i++){
        cout << "For " << i << " the node : ";
        for(int j=0 ; j<adj[i].size() ; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int computeDistance(vector<vector<int>> &adj , vector<int> &v1 , vector<int> &v2){
    int n = adj.size();
    int n1 = v1.size();
    int n2 = v2.size();

    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;

    vector<int> dis(n , 1e9);
    vector<int> vis(n , 0);

    for(int i=0 ; i<n1 ; i++){
        pq.push({0 , v1[i]});
        vis[v1[i]] = 1;
        dis[v1[i]] = 0;
    }

    for(int i=0 ; i<n2 ; i++){
        if(dis[v2[i]] == 0){
            return 0;
        }
        vis[v2[i]] = 1;
        dis[v2[i]] = 1e5;
    }


    while(!pq.empty()){
        int disNode = pq.top().first;
        int crntNode = pq.top().second;
        pq.pop();

        for(auto neigh : adj[crntNode]){
            int neighDis = disNode + 1;

            if(!vis[neigh] && (neighDis < dis[neigh] || dis[neigh] == 0)){
                pq.push({neighDis , neigh});
                dis[neigh] = neighDis;
            }else if(vis[neigh]){
                if(dis[neigh] == 1e5){
                    return disNode+1;
                }
            }
        }
    }

    cout << "These vertex set are not connected.\n";
    return INT_MAX;
}

int main(){
    int n , m;
    cout << "Enter number of nodes and edges : ";
    cin >> n >> m;

    vector<vector<int>> adj(n , vector<int>());
    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x , y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int n1;
    cout << "Enter number of element in first vertex set ( =<" << n << ") : ";
    cin >> n1;
    cout << "Enter all vertex : ";
    vector<int> v1(n1);
    for(int i=0 ; i<n1 ; i++){
        cin >> v1[i];
    }

    int n2;
    cout << "Enter number of element in second vertex set ( =<" << n << ") : ";
    cin >> n2;
    vector<int> v2(n2);
    cout << "Enter all vertex : ";
    for(int i=0 ; i<n2 ; i++){
        cin >> v2[i];
    }

    printAdjList(adj);

    int ans = computeDistance(adj , v1 , v2);

    cout << "desired answer : " << ans;
    
    return 0;
}