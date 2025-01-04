#include <iostream>
#define INF 100000 // A large value to represent infinity
#define V 19 // Number of vertices in the graph
using namespace std;
int alt[V][V][V];

#ifndef START_EMERGENCY_FLOYD_H
#define START_EMERGENCY_FLOYD_H

void all_shortest_alternatives(int graph[V][V] ){
    // initialize alt with V copies of graph
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                alt[k][i][j] = graph[i][j];
            }
        }
    }
    int dist[V][V];
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            dist[i][j] = graph[i][j];
        }
    }
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j]>dist[i][k]+dist[k][j] )
                    dist[i][j]=dist[i][k]+dist[k][j];
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int l = 0; l < V; ++l) { // l is the fault componentA


        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (alt[l][i][j]>alt[l][i][k]+alt[l][k][j] && (i!=l || j!=l))
                        alt[l][i][j]=alt[l][i][k]+alt[l][k][j];
                    else if (i==l || j==l)
                        alt[l][i][j]=INF; // reached faulty component

                }
            }
        }
    }
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout<<alt[0][i][j]<<" ";
        }
        cout<<endl;
    }


}
#endif //START_EMERGENCY_FLOYD_H
