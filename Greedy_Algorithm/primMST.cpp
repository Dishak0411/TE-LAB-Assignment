#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int primMST(vector<vector<pair<int, int>>> &adj, int V)
{
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    int totalCost = 0;
    
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (mstSet[u])
            continue;
        mstSet[u] = true;
        totalCost += key[u];

        for (auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (!mstSet[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << " (" << key[i] << ") " << endl;
    }
    return totalCost;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> adj(V);

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << "Cost of MST using Prim's Algorithm: " << primMST(adj, V) << endl;
    return 0;
}

// Greedy Concept:
// It greedily selects the smallest edge that connects a vertex in MST to a vertex outside it, growing the MST step-by-step.

// Time Complexity:
//     O(E log V) using priority queue (min-heap)
// Space Complexity:
//     O(V + E)
