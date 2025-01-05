#include <iostream>
#include <vector>
#include "CityMap.h"
#include "EventHandler.h"

vector<vector<int>> modified_road_network = road_network;
vector<vector<int>> modified_power_network = power_network;
vector<vector<int>> modified_DC_network = DC_network;
vector<vector<int>> modified_road_network_capacity = road_network_capacity;
vector<vector<int>> modified_power_network_capacity = power_network_capacity;
vector<vector<int>> modified_DC_network_capacity = DC_network_capacity;

/**************   Earthquake  **************/

void Earthquake::trigger() {

    /* Cut half the connections to the damaged node */
    int nof_damaged_edges = getEdges(modified_road_network, damaged_node) / 2;
    for(int i = 0; i < nof_damaged_edges;){
        if(modified_road_network[damaged_node][i] != 0){

            modified_road_network[damaged_node][i] = 0;
            modified_road_network[i][damaged_node] = 0;

            modified_power_network[damaged_node][i] = 0;
            modified_power_network[i][damaged_node] = 0;

            modified_DC_network[damaged_node][i] = 0;
            modified_DC_network[i][damaged_node] = 0;

            i++;
        }
    }
}

void Earthquake::handle() {

    /* Re-run MST to the modified power and DC graphs */

    /* Re-run Floyd-Warshall to the modified road network */

    /* A* from the three emergency centers to the damaged node */

}

/**************   Maintenance  **************/

void Maintenance::trigger() {
    /* Reduce or disable the ford-fulkeson capacity to the damaged node */

}

void Maintenance::handle() {
    /* Re-run ford Fulkerson */

    /* Re-run MST */

}

/**************   Traffic Congestion  **************/

void TrafficCongestion::trigger() {
    /* Increase the weights of edges connected to the congested node */
    for(int i = 0; i < N; i++){
        if(modified_road_network[damaged_node][i] != 0) {
            modified_road_network[damaged_node][i] *= 2;
            modified_road_network[i][damaged_node] *= 2;
        }
    }

    /* Decrease the edge capacity for the edges connected to the congested node */

}

void TrafficCongestion::handle(){
    /* Re-Run Floyd Warshall */

    /* Re-Run Fork-Fulkerson */

    /* Use A* (still being figured) */
}