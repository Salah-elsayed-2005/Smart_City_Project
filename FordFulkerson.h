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
    vector <bool> visited(6, false);
    queue<int>q;
    q.push(source);
    visited[source]= true;
    while (!q.empty()){
        int tmp=q.front();
        q.pop();
        for (int i = 0; i < adj[0].size(); ++i) {
            if (!visited[i] && adj[tmp][i] ){
                visited[i]=true;
                q.push(i);
                parent[i]=tmp;
            }
        }
    }
    return visited[sink];
}

int ford_fulkerson(vector<vector<int> > adj,int source,int sink){
    int max_flow=0;
    vector<int> parent(6,-1);

    while (bfs(adj,source,sink,parent)){
        int pathflow=INT_MAX; // we want to take the minimum bottleneck
        int s=sink;
        while (s != source){
            pathflow= min(pathflow,adj[parent[s]][s]);
            s=parent[s];
        }
        max_flow+=pathflow;
        int v=sink;
        while (v!=source){
            int u=parent[v];
            adj[u][v]-=pathflow;
            adj[v][u]+=pathflow;
            v=parent[v];
        }
    }
    return max_flow;

}


#endif //START_FORDFULKERSON_H
