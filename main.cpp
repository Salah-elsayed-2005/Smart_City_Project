#include <iostream>
#include "CityMap.h"
#include "FordFulkerson.h"
#include "MST.h"
#include "Functionalities.h"
using namespace std;

int main() {

    cout<<ford_fulkerson(road_network_capacity,0,9);
    /**********************************Test MST******************************************************/
    /*int n = 5;
    vector<vector<int>> graph = {
            {0, 1, 10},
            {1, 2, 5},
            {2, 3, 8},
            {3, 4, 12},
            {4, 1, 7}
    };

    
    vector<vector<int>>mst=kruskalMST(n, graph);
    for (auto &edge:mst) {
        cout<<edge[0]<<"--"<<edge[1]<<endl;
    }*/

  //  mainmenu();
    return 0;
}
