//
// Created by Se7s on 12/26/2024.
//

#include <bits/stdc++.h>
using namespace std;
#ifndef SMART_CITY_PROJECT_MST_H
#define SMART_CITY_PROJECT_MST_H

// DSU class for union-find operations
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int x) {       //time complexity for this function is O(α(n))
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Detect cycle function
    bool detectCycle(int x, int y) {    //time complexity for this function is O(α(n))
        return find(x) == find(y);  //have the same parent
    }

    // Union by rank with cycle detection
    bool unite(int x, int y) {  //time complexity for this function is O(α(n))
        if (detectCycle(x, y)) return false; // Cycle detected

        int rootX = find(x);
        int rootY = find(y);

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

vector<vector<int>> kruskalMST(int n, vector<vector<int>>& edges) { //time complexity is almost O(m log m) where m is the number of edges
    DSU dsu(n);
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2]; //a[2] and b[2] to get the edge weight
    });

    vector<vector<int>> mst;

    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1];
        if (dsu.unite(u, v)) {  // include them in the MST only if they don't form a cycle
            mst.push_back(edge);
        }
    }

    return mst;
}

#endif //SMART_CITY_PROJECT_MST_H
