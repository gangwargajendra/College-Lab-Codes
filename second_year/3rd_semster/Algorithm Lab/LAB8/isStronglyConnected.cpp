#include<iostream>
#include<vector>
using namespace std;

void DFS(vector<int> adjList[] , vector<int> &vis , int src){
    vis[src] = 1;
    for(auto it : adjList[src]){
        if(!vis[it]){
            DFS(adjList , vis ,it);
        }
    }
}

bool isStronglyConnected(vector<int> adjList[] , int v){
    vector<int> vis(v, 0);
    
    DFS(adjList , vis, 0);

    for(int i=0 ; i<v ; i++){
        if(vis[i] == 0) return false;
        else vis[i] = 0;
    }

    vector<int> adjListRev[v];
    for(int i=0 ; i<v ; i++){
        for(auto it : adjList[i]){
            adjListRev[it].push_back(i);
        }
    }

    DFS(adjListRev , vis , 0);

    for(int i=0 ; i<v ; i++){
        if(vis[i] == 0) return false;
    }
    return true;
}

int main(){
    int n , m;
    cout << "Enter number of vertices and edges : ";
    cin >> n >> m;

    vector<int> adjList[n];
    cout << "enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x,y;
        cin >> x >> y;
        adjList[x].push_back(y);
    }

    bool ans = isStronglyConnected(adjList , n);

    if(ans){
        cout << "given graoh is strongly connnected.";
    }else {
        cout << "given graph is not strongly connected.";
    }

    return 0;
}