#include <iostream>
#include <vector>
#include <cmath>
#include "CityMap.h"
#include "A_Star.h"
#include "FordFulkerson.h"
#include "Emergency_Floyd.h"
#include "MST.h"


#include "EventHandler.h"

vector<vector<int>> modified_road_network = road_network;
vector<vector<int>> modified_power_network = power_network;
vector<vector<int>> modified_DC_network = DC_network;
vector<vector<int>> modified_road_network_capacity = road_network_capacity;
vector<vector<int>> modified_power_network_capacity = power_network_capacity;
vector<vector<int>> modified_DC_network_capacity = DC_network_capacity;

/**************   Earthquake  **************/

vector<vector<vector<int>>> road_network_trigger_steps;
vector<vector<vector<int>>> power_network_trigger_steps;
vector<vector<vector<int>>> DC_network_trigger_steps;

vector<vector<vector<int>>> power_network_handle_steps(N, vector<vector<int>>(N, vector<int>(N, 0)));
vector<vector<vector<int>>> DC_network_handle_steps(N, vector<vector<int>>(N, vector<int>(N, 0)));



vector<vector<int>> emergency_routes(3, vector<int>());

vector<vector<int>> makeEdgeList(vector<vector<int>> &graph){
    vector<vector<int>> edges;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (graph[i][j] != 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    return edges;
}

void Earthquake::trigger() {
    /* Initialize with the original graph */
    road_network_trigger_steps.push_back(modified_road_network);
    power_network_trigger_steps.push_back(modified_power_network);
    DC_network_trigger_steps.push_back(modified_DC_network);

    /* Cut half the connections to the damaged node */
    int nof_damaged_edges = (int)round(getEdges(modified_road_network, damaged_node) / 2.0);

    for(int i = 0; i < nof_damaged_edges;){
        if(modified_road_network[damaged_node][i] != 0){

            modified_road_network[damaged_node][i] = 0;
            modified_road_network[i][damaged_node] = 0;

            modified_power_network[damaged_node][i] = 0;
            modified_power_network[i][damaged_node] = 0;

            modified_DC_network[damaged_node][i] = 0;
            modified_DC_network[i][damaged_node] = 0;

            road_network_trigger_steps.push_back(modified_road_network);
            power_network_trigger_steps.push_back(modified_power_network);
            DC_network_trigger_steps.push_back(modified_DC_network);

            i++;
        }
    }

    /* Remove Ford capacities */ /////////////////// SALAH
}


/*****************************  to the graph  ***************************/
vector<vector<vector<int>>> Earthquake::get_road_network_trigger_steps() {
    return road_network_trigger_steps;
}

vector<vector<vector<int>>> Earthquake::get_power_network_trigger_steps() {
    return power_network_trigger_steps;
}

vector<vector<vector<int>>> Earthquake::get_DC_network_trigger_steps() {
    return DC_network_trigger_steps;
}
/*************************************************************************/

void Earthquake::handle() {

    /* Re-run MST to the modified power and DC graphs */
    vector<vector<int>>powerEdges= makeEdgeList(modified_power_network); //construct the edge list for the power network
    kruskalMST(N,powerEdges,power_network_handle_steps);    //find the MST for the power network with each step

    vector<vector<int>>DCEdges= makeEdgeList(modified_DC_network); //construct the edge list for the DC network
    kruskalMST(N,DCEdges,DC_network_handle_steps);   //find the MST for the DC network with each step


    /* A* from the three emergency centers to the damaged node */

    int shortest_path;

    A_Star(road_network, HOSPITAL, damaged_node, shortest_path, emergency_routes[0]);
    A_Star(road_network, POLICE_STATION, damaged_node, shortest_path, emergency_routes[1]);
    A_Star(road_network, FIRE_STATION, damaged_node, shortest_path, emergency_routes[2]);

}
/*****************************  to the graph  ***************************/

vector<vector<vector<int>>> Earthquake::get_power_network_handle_steps() {
    return power_network_handle_steps;
}

vector<vector<vector<int>>> Earthquake::get_DC_network_handle_steps() {
    return DC_network_handle_steps;
}

vector<vector<int>> Earthquake::get_emergency_routes() {
    return emergency_routes;
}
/*************************************************************************/


/**************   Maintenance  **************/

void Maintenance::trigger() {

    power_network_trigger_steps.push_back(modified_power_network);
    DC_network_trigger_steps.push_back(modified_DC_network);

    /* Disable damaged node */

    if(damaged_node >= 8 && damaged_node <= 10) {
        for (int i = 0; i < N; i++) {
            if (modified_power_network[damaged_node][i] != 0) {

                modified_power_network[damaged_node][i] = 0;
                modified_power_network[i][damaged_node] = 0;

                power_network_trigger_steps.push_back(modified_power_network);
            }
        }
    }
    else if (damaged_node >= 11 && damaged_node <= 13){
        for (int i = 0; i < N; i++) {
            if (modified_DC_network[damaged_node][i] != 0) {

                modified_DC_network[damaged_node][i] = 0;
                modified_DC_network[i][damaged_node] = 0;

                DC_network_trigger_steps.push_back(modified_DC_network);
            }
        }
    }

    /* Reduce or disable the ford-fulkeson capacity to the damaged node */
    /////////////////////// SALAH
}

/*****************************  to the graph  ***************************/

vector<vector<vector<int>>> Maintenance::get_road_network_trigger_steps() {
    return road_network_trigger_steps;
}

vector<vector<vector<int>>> Maintenance::get_power_network_trigger_steps() {
    return power_network_trigger_steps;
}

vector<vector<vector<int>>> Maintenance::get_DC_network_trigger_steps() {
    return DC_network_trigger_steps;
}
/*************************************************************************/


void Maintenance::handle() {
    /* Re-run ford Fulkerson */

    /* Re-run MST */
    vector<vector<int>>powerEdges= makeEdgeList(modified_power_network); //construct the edge list for the power network
    kruskalMST(N,powerEdges,power_network_handle_steps);    //find the MST for the power network with each step

    vector<vector<int>>DCEdges= makeEdgeList(modified_DC_network); //construct the edge list for the DC network
    kruskalMST(N,DCEdges,DC_network_handle_steps);   //find the MST for the DC network with each step
}

/*****************************  to the graph  ***************************/

vector<vector<vector<int>>> Maintenance::get_power_network_handle_steps() {
    return power_network_handle_steps;
}

vector<vector<vector<int>>> Maintenance::get_DC_network_handle_steps() {
    return DC_network_handle_steps;
}
/*************************************************************************/


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
    //////////////// SALAH

}
/*************************************************************************/


void TrafficCongestion::handle(){
    /* Re-Run Floyd Warshall */

    /* Re-Run Ford-Fulkerson */
    /////////////////// SALAH

}
