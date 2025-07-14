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

bool isCycle(vector<int> adjList[], int n){
    queue<pair<int,int>> q;
    q.push({0, -1});
    vector<int> vis(n , 0);
    vis[0] = 1;
    while(!q.empty()){
        int crnt = q.front().first;
        int prnt = q.front().second;
        q.pop();
        for(auto it :adjList[crnt]){
            if(!vis[it]){
                vis[it] = 1;
                q.push({it , crnt});
            }else if(vis[it] && it != prnt){
                return true;
            }
        }
    }
    return false;
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

    bool ans = isCycle(adjList ,n);
    
    if(ans){
        cout << "there is a cycle.....";
    }else{
        cout << "there is not a cycle.....";
    }
    return 0;
}