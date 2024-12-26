//
// Created by salah elsayed on 12/21/2024.
//
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
#ifndef START_FORDFULKERSON_H
#define START_FORDFULKERSON_H






bool bfs(vector<vector<int> > &adj, int source, int sink, vector<int>&parent ){
    int n=adj[0].size();
    vector <bool> visited(n, false);
    queue<int>q;
    q.push(source);
    visited[source]= true;
    while (!q.empty()){
        int tmp=q.front();
        q.pop();
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && adj[tmp][i] ){
                visited[i]=true;
                q.push(i);
                parent[i]=tmp;
            }
        }
    }
    return visited[sink];
}

int ford_fulkerson(vector<vector<int> > cap, int source, int sink){
    int max_flow=0;
    int n=cap[0].size();
    vector<int> parent(n,-1);

    while (bfs(cap, source, sink, parent)){
        int pathflow=INT_MAX; // we want to take the minimum bottleneck
        int s=sink;
        while (s != source){
            pathflow= min(pathflow, cap[parent[s]][s]);
            s=parent[s];
        }
        max_flow+=pathflow;
        int v=sink;
        while (v!=source){
            int u=parent[v];
            cap[u][v]-=pathflow;
            cap[v][u]+=pathflow;
            v=parent[v];
        }
    }
    return max_flow;

}


#endif //START_FORDFULKERSON_H
