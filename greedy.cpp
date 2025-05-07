#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// ======== Prim's Algorithm ========
int minKey(vector<int>& key, vector<bool>& mstSet, int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V), key(V, INT_MAX);
    vector<bool> mstSet(V, false);
    key[0] = 0, parent[0] = -1;

    int totalCost = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    cout << "Prim's MST:\nEdge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]];
    }
    cout << "Total Cost of MST: " << totalCost << "\n";
}

// ======== Kruskal's Algorithm ========
struct Edge {
    int src, dest, weight;
    bool operator<(Edge const& other) const {
        return weight < other.weight;
    }
};

int find(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = find(parent, x), yroot = find(parent, y);
    if (rank[xroot] < rank[yroot]) parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot]) parent[yroot] = xroot;
    else { parent[yroot] = xroot; rank[xroot]++; }
}

void kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end());
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    int totalCost = 0;
    cout << "Kruskal's MST:\nEdge \tWeight\n";
    for (Edge& edge : edges) {
        int x = find(parent, edge.src);
        int y = find(parent, edge.dest);
        if (x != y) {
            cout << edge.src << " - " << edge.dest << "\t" << edge.weight << "\n";
            totalCost += edge.weight;
            unionSet(parent, rank, x, y);
        }
    }
    cout << "Total Cost of MST: " << totalCost << "\n";
}

// ======== Dijkstra's Algorithm ========
int minDistance(vector<int>& dist, vector<bool>& sptSet, int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(vector<vector<int>>& graph, int src, int V) {
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    cout << "Dijkstra's Shortest Paths from Node " << src << ":\n";
    cout << "Vertex\tDistance\n";
    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << "\n";
}

// ======== Job Scheduling Problem ========
struct Job {
    char id;
    int deadline;
    int profit;
};

bool jobCompare(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), jobCompare);
    int n = jobs.size();
    vector<bool> slot(n, false);
    vector<char> result(n);

    for (int i = 0; i < n; i++) {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                slot[j] = true;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    cout << "Scheduled Jobs for Max Profit: ";
    for (int i = 0; i < n; i++)
        if (slot[i]) cout << result[i] << " ";
    cout << "\n";
}

// ======== Main Menu ========
int main() {
    int choice;
    cout << "Choose an Algorithm to Run:\n";
    cout << "1. Prim's MST\n";
    cout << "2. Kruskal's MST\n";
    cout << "3. Dijkstra's Shortest Path\n";
    cout << "4. Job Scheduling Problem\n";
    cout << "Enter choice (1-4): ";
    cin >> choice;

    if (choice == 1) {
        int V;
        cout << "Enter number of vertices: ";
        cin >> V;
        vector<vector<int>> graph(V, vector<int>(V));
        cout << "Enter adjacency matrix (0 if no edge):\n";
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                cin >> graph[i][j];
        primMST(graph, V);
    }

    else if (choice == 2) {
        int E, V;
        cout << "Enter number of vertices and edges: ";
        cin >> V >> E;
        vector<Edge> edges(E);
        cout << "Enter edges (src dest weight):\n";
        for (int i = 0; i < E; i++)
            cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
        kruskalMST(edges, V);
    }

    else if (choice == 3) {
        int V, src;
        cout << "Enter number of vertices: ";
        cin >> V;
        vector<vector<int>> graph(V, vector<int>(V));
        cout << "Enter adjacency matrix (0 if no edge):\n";
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                cin >> graph[i][j];
        cout << "Enter source vertex: ";
        cin >> src;
        dijkstra(graph, src, V);
    }

    else if (choice == 4) {
        int n;
        cout << "Enter number of jobs: ";
        cin >> n;
        vector<Job> jobs(n);
        cout << "Enter job details (id deadline profit):\n";
        for (int i = 0; i < n; i++)
            cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
        jobScheduling(jobs);
    }

    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
