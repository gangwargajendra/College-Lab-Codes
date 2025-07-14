#include<iostream>
#include<vector>
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

void printAdjList(vector<vector<int>> adjList){
    int n = adjList.size();
    cout << "Adjacency matrix : " << endl;
    for(int i=0 ; i<n ; i++){
        cout << "for node " << i << " : ";
        for(auto it : adjList[i]){
            cout << it << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> makeAdjList(vector<vector<int>> adjMat){
    int n = adjMat.size();
    vector<vector<int>> adjList(n , vector<int>());

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            if(adjMat[i][j] == 1){
                adjList[i].push_back(j);
            }
        }
    } 
    return adjList;
}

vector<vector<int>> makeAdjMatrix(vector<vector<int>> adjList){
    int n = adjList.size();

    vector<vector<int>> adjMat(n , vector<int>(n , 0));

    for(int i=0 ; i<n ; i++){
        for(auto it : adjList[i]){
            adjMat[i][it] = 1;
            adjMat[it][i] = 1;
        }
    }
    return adjMat;
}

int main(){
    int n,m;
    cout << "Enter number of nodes and edges : ";
    cin >> n >> m;

    vector<vector<int>> adjMat(n , vector<int>(n , 0));

    cout << "Enter all edges : ";
    for(int i=0 ; i<m ; i++){
        int x, y;
        cin >> x >> y;
        adjMat[x][y] = 1;
        adjMat[y][x] = 1;
    }

    printMatrix(adjMat);

    vector<vector<int>> adjList = makeAdjList(adjMat);
    
    printAdjList(adjList);

    vector<vector<int>> newAdjMat = makeAdjMatrix(adjList);

    printMatrix(newAdjMat);
    
    return 0;
}