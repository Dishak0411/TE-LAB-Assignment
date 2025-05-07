#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Graph
{
public:
    void addEdge(int u, int v, vector<vector<int>> &adjList)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void bfs(vector<vector<int>> &adjList, int s)
    {
        queue<int> q;
        vector<bool> visited(adjList.size(), false);
        visited[s] = true;
        q.push(s);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int i : adjList[curr])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    void dfs(vector<vector<int>> &adjList, int s)
    {
        stack<int> st;
        vector<bool> visited(adjList.size(), false);
        visited[s] = true;
        st.push(s);

        while (!st.empty())
        {
            int curr = st.top();
            st.pop();
            cout << curr << " ";

            for (int i : adjList[curr])
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    st.push(i);
                }
            }
        }
    }

    void dfsrh(vector<vector<int>> &adjList, int s, vector<bool> &visited)
    {
        visited[s] = true;
        cout << s << " ";

        for (int i : adjList[s])
        {
            if (!visited[i])
            {
                dfsrh(adjList, i, visited);
            }
        }
    }

    void dfs_rec(vector<vector<int>> &adjList, int s)
    {
        vector<bool> visited(adjList.size(), false);
        dfsrh(adjList, s, visited);
    }

    void LimitedBFS(vector<vector<int>> &adjList, int s, int limit, int search)
    {
        queue<int> q;
        vector<bool> visited(adjList.size(), false);

        visited[s] = true;
        q.push(s);

        while (!q.empty() && limit--)
        {
            int curr = q.front();
            q.pop();

            for (int x : adjList[curr])
            {
                if (x == search)
                {
                    cout << "Found" << endl;
                    return;
                }
                if (!visited[x])
                {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }
        cout << "Not Found" << endl;
    }

    void LimitedDFS(vector<vector<int>> &adjList, int s, int limit, int search)
    {
        vector<bool> visited(adjList.size(), false);
        if (!dfsLimitedHelper(adjList, s, limit, search, visited))
        {
            cout << "Not Found" << endl;
        }
    }

private:
    bool dfsLimitedHelper(vector<vector<int>> &adjList, int s, int limit, int search, vector<bool> &visited)
    {
        if (limit < 0)
            return false;

        visited[s] = true;
        cout << s << " ";

        if (s == search)
        {
            cout << "\nFound" << endl;
            return true;
        }

        for (int i : adjList[s])
        {
            if (!visited[i])
            {
                if (dfsLimitedHelper(adjList, i, limit - 1, search, visited))
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    Graph gh;

    int V, E, u, v, st, ch;
    int count = 1;

    cout << "Operations: " << endl;
    cout << "1. Create Graph\n2. Breadth First Search\n3. Depth First Search(Non- Recursive)\n4. Depth First Search(Recursive)\n5. Limited BFS\n6. Limited DFS" << endl;

    vector<vector<int>> adj;

    while (count == 1)
    {
        cout << "Enter Operation: " << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter number of vertices: ";
            cin >> V;
            cout << "Enter number of edges: ";
            cin >> E;

            adj.resize(V);

            cout << "Enter the edges (u, v): \n";
            for (int i = 0; i < E; i++)
            {
                cin >> u >> v;
                gh.addEdge(u, v, adj);
            }
            break;

        case 2:
            cout << "Enter source node for BFS: ";
            cin >> st;
            gh.bfs(adj, st);
            cout << endl;
            break;

        case 3:
            cout << "Enter source node for DFS(Non-Recursive): ";
            cin >> st;
            gh.dfs(adj, st);
            cout << endl;
            break;

        case 4:
            cout << "Enter source node for DFS(Recursive): ";
            cin >> st;
            gh.dfs_rec(adj, st);
            cout << endl;
            break;

        case 5:
        {
            int limit, search;
            cout << "Enter source node for Limited BFS: ";
            cin >> st;
            cout << "Enter the limit for BFS: ";
            cin >> limit;
            cout << "Enter the node to search in Limited BFS: ";
            cin >> search;
            gh.LimitedBFS(adj, st, limit, search);
            break;
        }

        case 6:
        {
            int limit, search;
            cout << "Enter source node for Limited DFS: ";
            cin >> st;
            cout << "Enter the limit for DFS: ";
            cin >> limit;
            cout << "Enter the node to search in Limited DFS: ";
            cin >> search;
            gh.LimitedDFS(adj, st, limit, search);
            break;
        }

        default:
            cout << "Invalid operation! Try again." << endl;
            break;
        }

        cout << "Repeat the operation (1/0): ";
        cin >> count;
    }

    return 0;
}