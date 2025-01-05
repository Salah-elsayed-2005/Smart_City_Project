//
// Created by salah elsayed on 12/21/2024.
//
#include <vector>
using namespace std;
#ifndef START_FORDFULKERSON_H
#define START_FORDFULKERSON_H


bool bfs(std::vector<std::vector<int>>& graph, int source, int sink, std::vector<int>& parent);
int ford_fulkerson(std::vector<std::vector<int>> graph, int source, int sink);


#endif //START_FORDFULKERSON_H
