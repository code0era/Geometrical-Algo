#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n; // number of vertices
vector<vector<int>> graph;

// Prim's algorithm to build MST
vector<pair<int,int>> primMST() {
    vector<int> key(n+1, INF);
    vector<int> parent(n+1, -1);
    vector<bool> inMST(n+1, false);

    key[1] = 0; // start from vertex 1
    for(int count=0; count<n-1; count++) {
        int u=-1;
        int minKey=INF;
        for(int v=1; v<=n; v++) {
            if(!inMST[v] && key[v]<minKey) {
                minKey=key[v];
                u=v;
            }
        }

        inMST[u]=true;

        for(int v=1; v<=n; v++) {
            if(graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    vector<pair<int,int>> mstEdges;
    for(int i=2; i<=n; i++) {
        mstEdges.push_back({parent[i], i});
    }
    return mstEdges;
}

// DFS to get preorder traversal of MST
void dfs(int u, vector<vector<int>>& mstAdj, vector<bool>& visited, vector<int>& tour) {
    visited[u] = true;
    tour.push_back(u);
    for(int v : mstAdj[u]) {
        if(!visited[v]) dfs(v, mstAdj, visited, tour);
    }
}

int main() {
    n = 6;
    graph = {
        {0,0,0,0,0,0,0},   
        {0,0,10,0,0,18,16},
        {0,10,0,12,0,20,0},
        {0,0,12,0,15,10,0},
        {0,0,0,15,0,40,0}, 
        {0,18,20,10,40,0,8},
        {0,16,0,0,0,8,0}   
    };

    // Get MST
    vector<pair<int,int>> mstEdges = primMST();

    // Build MST adjacency list
    vector<vector<int>> mstAdj(n+1);
    for(auto e : mstEdges) {
        int u=e.first, v=e.second;
        mstAdj[u].push_back(v);
        mstAdj[v].push_back(u);
    }

    //  DFS preorder traversal
    vector<bool> visited(n+1,false);
    vector<int> tour;
    dfs(1, mstAdj, visited, tour);
    tour.push_back(1); // return to start

    //  Calculate tour cost
    int cost=0;
    for(int i=0; i<(int)tour.size()-1; i++) {
        cost += graph[tour[i]][tour[i+1]];
    }

    // Print tour and cost
    cout << "Approximate TSP Tour: ";
    for(int v : tour) cout << v << " ";
    cout << "\nTour Cost = " << cost << "\n";
    cout << "Approximation Ratio <= 2 (MST-based algorithm)\n";

    return 0;
}
