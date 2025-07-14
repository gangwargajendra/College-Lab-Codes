#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

void DFS(int src,vector<int> adjList[] , stack<int> &st ,vector<int> &vis){
    vis[src] = 1;
    for(auto it : adjList[src]){
        if(!vis[it]){
            DFS(it , adjList , st , vis);
        }
    }
    st.push(src);
}

void DFSnew(int src,vector<int> adjList[],vector<int> &vis
,vector<int> &com){
    vis[src] = 1;
    com.push_back(src);
    for(auto it : adjList[src]){
        if(!vis[it]){
            DFSnew(it, adjList,vis, com);
        }
    }
}

vector<vector<int>> connectedcomponents(int v, vector<vector<int>>& edges) {
    vector<int> adjListRev[v];
    vector<int> adjList[v];
    for(int i=0 ; i<edges.size() ; i++){
        int x = edges[i][0];
        int y = edges[i][1];
        adjList[x].push_back(y);
        adjListRev[y].push_back(x);
    }
    vector<int> vis(v,0);
    stack<int> st;
    for(int i=0 ; i<v ; i++){
        if(!vis[i]){
            DFS(i, adjListRev , st , vis);
        }
    }
    
    vector<vector<int>> components;
    
    for(int i=0 ; i<v ; i++) vis[i] = 0;
    
    while(!st.empty()){
        int x = st.top();
        st.pop();
        if(!vis[x]){
            vector<int> com;
            DFSnew(x ,adjList, vis,com);
            sort(com.begin(), com.end());
            components.push_back(com);
        }
    }
    return components;
}

int main(){
    int n,m;
    cout << "Enter number of vertices and edges : ";
    cin >> n >> m;

    vector<vector<int>> edges;
    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x,y;
        cin >> x >> y;
        edges.push_back({x,y});
    }

    vector<vector<int>> ans = connectedcomponents(n , edges);

    cout << "Strongly connected componenets : " << endl;
    for(int i=0 ; i<ans.size() ; i++){
        cout << i+1 << ". ";
        for(auto it : ans[i]){
            cout << it << " ";
        }
        cout << endl;
    }
    return 0;
}