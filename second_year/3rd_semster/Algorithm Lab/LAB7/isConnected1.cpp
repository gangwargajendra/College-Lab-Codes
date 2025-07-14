#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void printAdjList(vector<int> adjList[] , int n){
    cout << "Adjacency matrix : " << endl;
    for(int i=0 ; i<n ; i++){
        cout << "for node " << i << " : ";
        for(auto it : adjList[i]){
            cout << it << " ";
        }
        cout << endl;
    }
}

bool isConnected(vector<int> adjList[], int n){
    queue<int> q;
    q.push(0);
    vector<int> vis(n , 0);
    vis[0] = 1;
    while(!q.empty()){
        int crnt = q.front();
        q.pop();
        for(auto it :adjList[crnt]){
            if(!vis[it]){
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    for(int i=0 ; i<n ; i++){
        if(!vis[i]) return false;
    }
    return true;
}

int main(){
    int n,m;
    cout << "Enter number of nodes and edges : ";
    cin >> n >> m;

    vector<int> adjList[n];

    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x, y;
        cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
    printAdjList(adjList ,  n);

    bool ans = isConnected(adjList ,n);
    
    if(ans){
        cout << "It is a connected graph.....";
    }else{
        cout << "it is not a connected graph.....";
    }
    
    return 0;
}