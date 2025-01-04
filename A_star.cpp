#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include "CityMap.h"
#include "A_Star.h"

int HeuristicValue(vector<vector<int>> &graph, int source, int goal){
    return (int)round(sqrt(pow((City_coordinates[goal].x - City_coordinates[source].x), 2) +
                        pow((City_coordinates[goal].y - City_coordinates[source].y), 2)));
}



struct CompareSecond {
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    }
};

bool IsHeuristicConsistent(vector<vector<int>> &graph) {
    int n = graph.size();
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (graph[x][y] != 0) { // There's an edge between x and y
                int hx = HeuristicValue(graph, x, y); // h(x)
                int hy = HeuristicValue(graph, y, y); // h(y) (heuristic to itself = 0)
                int cost = graph[x][y]; // c(x, y)

                if (hx > cost + hy) { // Check consistency
                    cout << "Inconsistent heuristic between nodes " << x << " and " << y << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

void A_Star(vector<vector<int>> &graph, int source, int goal, int &shortest_path, vector<int> &route){
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    shortest_path = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> pq;

    dist[source] = 0;
    pq.push({source, dist[source] + HeuristicValue(graph, source, goal)});


    while(!pq.empty()){
        int curr = pq.top().first;
        pq.pop();

        if(curr == goal){
            shortest_path = dist[curr];
            while(curr != -1){
                route.push_back(curr);
                curr = parent[curr];
            }
            reverse(route.begin(), route.end());
            return;

        }
        else {
            if(!visited[curr]) {
                visited[curr] = true;
                for (int neighbor = 0; neighbor < n; neighbor++) {
                    if (graph[curr][neighbor] != 0 && !visited[neighbor]) {
                        int g = dist[curr] + graph[curr][neighbor];

                        if (g < dist[neighbor]){
                            dist[neighbor] = g;
                            parent[neighbor] = curr;
                            pq.push({neighbor, dist[neighbor] + HeuristicValue(graph, neighbor, goal)});
                        }
                    }
                }
            }
        }
    }
}

