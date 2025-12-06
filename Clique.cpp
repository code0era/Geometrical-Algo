#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> adj;
map<int, set<set<int>>> all_cliques;

bool isConnectedToAll(int node, const vector<int> &clique)
{
    for (int v : clique)
    {
        bool found = false;
        for (int neighbor : adj[node])
        {
            if (neighbor == v)
            {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void dfs(vector<int> &clique, vector<bool> &visited, int start)
{
    if (clique.size() >= 2)
    {
        set<int> clique_set(clique.begin(), clique.end());
        all_cliques[clique.size()].insert(clique_set);
    }

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i] && isConnectedToAll(i, clique))
        {
            visited[i] = true;
            clique.push_back(i);
            dfs(clique, visited, i);
            clique.pop_back();
            visited[i] = false;
        }
    }
}

int main()
{
    n = 100;
    adj = vector<vector<int>>(n);

    vector<pair<int, int>> edges = {
        {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {5, 6}, {5, 7}, {5, 8}, {6, 7}, {6, 8}, {7, 8}, {7, 9}};
    // vector<pair<int, int>> edges = {
    //     {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}, {4, 5}, {5, 6}, {4, 6}, {6, 7}, {7, 8}, {6, 8}, {8, 9}, {9, 10}, {8, 10}, {3, 5}, {2, 6}, {1, 7}};
    // vector<pair<int, int>> edges = {
    //     {1, 2}, {2, 3}, {3, 1}, {4, 5}, {5, 6}, {4, 6}, {7, 8}, {8, 9}, {7, 9}, {1, 4}, {2, 5}, {3, 6}, {9, 10}, {8, 10}, {7, 10}};

    for (auto [u, v] : edges)
    {
        adj[u].push_back(v);

        adj[v].push_back(u);
    }

    for (int i = 0; i < n; ++i)
    {
        vector<int> clique = {i};
        vector<bool> visited(n, false);
        visited[i] = true;
        dfs(clique, visited, i);
    }

    for (auto &[size, cliques] : all_cliques)
    {
        cout << "Cliques of size " << size << ":\n";
        for (auto &group : cliques)
        {
            cout << "{ ";
            for (int v : group)
                cout << v << " ";
            cout << "}\n";
        }
        cout << "Total: " << cliques.size() << "\n\n";
    }

    return 0;
}
