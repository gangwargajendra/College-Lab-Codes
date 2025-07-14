#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void printMatrix(vector<vector<int>> mat){
    int n= mat.size();
    cout << "matrix : " << endl;
    for(int i=0 ; i<n ; i++){
        cout << "for " << i << " rows : ";
        for(int j=0 ; j<n ; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

bool isConnected(vector<vector<int>> &adjMat){
    int n = adjMat.size();
    queue<int> q;
    vector<int> vis(n ,0);
    vis[0] = 1;
    q.push(0);
    while(!q.empty()){
        int row = q.front();
        q.pop();
        for(int i=0 ; i<n ; i++){
            if(adjMat[row][i] && !vis[i]){
                vis[i] = 1;
                q.push(i);
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

    vector<vector<int>> adjMat(n , vector<int>(n,0));

    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x, y;
        cin >> x >> y;
        adjMat[x][y] = 1;
        adjMat[y][x] = 1;
    }
    printMatrix(adjMat);

    bool ans = isConnected(adjMat);
    
    if(ans){
        cout << "It is a connected graph.....";
    }else{
        cout << "it is not a connected graph.....";
    }
    return 0;
}