#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

struct State {
    vector<vector<int>> residualGraph;
    vector<bool> visited;
    vector<pair<int, int>> exploredEdges;
};

bool bfs(vector<vector<int>> &adj, int source, int sink, vector<int> &parent, vector<bool> &visited, vector<pair<int, int>> &exploredEdges) {
    int n = adj.size();
    visited.assign(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && adj[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                exploredEdges.push_back({u, v});
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
}

vector<State> ford_fulkerson(vector<vector<int>> cap, int source, int sink) {
    int n = cap.size();
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    vector<pair<int, int>> exploredEdges;
    vector<State> steps;

    while (bfs(cap, source, sink, parent, visited, exploredEdges)) {
        int path_flow = INT_MAX;
        int v = sink;

        while (v != source) {
            int u = parent[v];
            path_flow = min(path_flow, cap[u][v]);
            v = u;
        }

        v = sink;
        while (v != source) {
            int u = parent[v];
            cap[u][v] -= path_flow;
            cap[v][u] += path_flow;
            v = u;
        }

        steps.push_back({cap, visited, exploredEdges});
        exploredEdges.clear();
    }

    return steps;
}
