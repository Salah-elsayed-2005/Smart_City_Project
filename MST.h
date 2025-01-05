//
// Created by Se7s on 12/26/2024.
//

#include <bits/stdc++.h>
using namespace std;
#ifndef SMART_CITY_PROJECT_MST_H
#define SMART_CITY_PROJECT_MST_H
using namespace std;

// DSU class for union-find operations
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n);

    int find(int x);
    bool detectCycle(int x, int y);
    bool unite(int x, int y);
};

// Kruskal's MST function
vector<vector<int>> kruskalMST(int n, vector<vector<int>>& edges, vector<vector<vector<int>>>& steps);

#endif //SMART_CITY_PROJECT_MST_H
