// used to find minimum Spanning tree

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Disjoint Data Structure
class DisjointSet {
public:
    vector<int> parent , rank ,size;  // rank is like height with slight change

public:
    DisjointSet(int n) {
        rank.resize(n+1 , 0);
        parent.resize(n+1);
        size.resize(n+1 , 1);

        for(int i=0 ; i<n+1 ; i++){
            parent[i] = i;
        }
    }

    int findUPar(int node){
        if(node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void UnionByRank(int u , int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }else if(rank[ulp_u] > rank[ulp_v]){
            parent[ulp_v] = ulp_u;
        }else{
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void UnionBySize(int u , int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        // this peace of line code is same as else condition so we can ignore this
        // else if(size[ulp_u] > size[ulp_v]){
        //     parent[ulp_v] = ulp_u;
        //     size[ulp_u] += size[ulp_v];
        // }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];  
        }
    }
};

vector<pair<int,pair<int,int>>> spanningTree(int n , vector<pair<int, pair<int, int>>> &edges){
    int m = edges.size();

    DisjointSet ds(n);

    sort(edges.begin() , edges.end());

    vector<pair<int,pair<int,int>>> mst;
    int mstWeight = 0;

    for(int i=0 ; i<m ; i++){
        int weight = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        if(ds.findUPar(u) != ds.findUPar(v)){
            mst.push_back({weight , {u , v}});
            mstWeight += weight;
            ds.UnionByRank(u , v);
        }
    }
    return mst;
}

int main(){
    int n , m;
    cout << "Enter number of nodes and edges : ";
    cin >> n >> m;

    vector<pair<int , pair<int,int>>> edges;
    cout << "Enter all edges and their weight : ";
    for(int i=0 ; i<m ; i++){
        int x , y , w;
        cin >> x >> y >> w;
        edges.push_back({w , {x , y}});
    } 

    vector<pair<int,pair<int,int>>> mst = spanningTree(n , edges);

    for(int i=0 ; i<mst.size() ; i++){
        cout << "edges " << i+1 << " : " << edges[i].second.first << " -> " << edges[i].second.second << " (" << edges[i].first << ")" << endl;
    }
}