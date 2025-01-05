//
// Created by salah elsayed on 1/5/2025.
//
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;
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
    vector<vector<int>> flow(n, vector<int>(n, 0));

    while (bfs(cap, source, sink, parent)){

        int pathflow=INT_MAX; // we want to take the minimum bottleneck
        vector<int> currentPath;
        int s=sink;
        while (s != source){
            currentPath.push_back(s);
            pathflow= min(pathflow, cap[parent[s]][s]);
            s=parent[s];
        }
        currentPath.push_back(source);
        reverse(currentPath.begin(), currentPath.end());
        max_flow+=pathflow;


        int v=sink;
        while (v!=source){
            int u=parent[v];
            cap[u][v]-=pathflow;
            cap[v][u]+=pathflow;
            flow[u][v] += pathflow;  // Add flow to the forward edge
            flow[v][u] -= pathflow;  // Subtract flow from the reverse edge
            v=parent[v];

        }

    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(flow[i][j] < 0) {
                flow[i][j] = 0;
            }
        }
    }
  /*  for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<<flow[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<flow[7][9]<<endl;
    cout<<flow[9][7]<<endl;
    cout<<flow[1][2]<<endl;
    cout<<flow[2][1]<<endl;
  */
    return max_flow;

}