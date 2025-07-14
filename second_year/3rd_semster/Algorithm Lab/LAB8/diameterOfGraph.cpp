#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int BFS(vector<int> adjList[] , vector<bool> &vis , int src){
    int maxDis = 0;
    queue<int> q;
    q.push(src);
    vis[src] = true;

    while(!q.empty()){
        int levelSize = q.size();
        for(int i=0 ; i<levelSize ; i++){
            int crnt = q.front();
            q.pop();

            for(auto it : adjList[crnt]){
                if(!vis[it]){
                    q.push(it);
                    vis[it] = true;
                }
            }
        }
        maxDis++;
    }
    return maxDis;
}

int diameter(int v , vector<int> adjList[]){
    int maxDis = -1;
    vector<bool> vis(v , false);
    for(int i=0 ; i<v ; i++){
        int dis = BFS(adjList , vis , i);
        fill(vis.begin(),vis.end(),false);
        maxDis = max(maxDis , dis);
    }
    return maxDis;
}

int main(){
    int n, m;
    cout << "Enter number of vertices and edges : ";
    cin >> n >> m;

    vector<int> adjList[n];
    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x,y;
        cin >>x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }

    int di = diameter(n , adjList);

    cout << "diameter of the graph : " << di ;
    return 0;
}
