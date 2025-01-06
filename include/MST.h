#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <deque>
#include <bitset>
#include <cassert>
#include <numeric>

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
