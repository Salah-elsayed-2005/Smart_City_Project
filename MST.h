#ifndef MST_H
#define MST_H

#include <vector>
#include <algorithm>
using namespace std;

struct MSTState {
    vector<pair<int, int>> mstEdges; // Edges in the MST so far
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

vector<MSTState> kruskalMST(int n, vector<vector<int>> &edges) {
    DSU dsu(n);
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });

    vector<MSTState> states;
    vector<pair<int, int>> mstEdges;

    for (const auto &edge : edges) {
        if (dsu.unite(edge[0], edge[1])) {
            mstEdges.push_back({edge[0], edge[1]});
            states.push_back({mstEdges});
        }
    }

    return states;
}

#endif
