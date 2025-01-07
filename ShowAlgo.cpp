#include <iostream>
#include <vector>
#include "CityMap.h"
#include "A_Star.h"
#include "MST.h"
#include "FordFulkerson.h"
#include "EventHandler.h"
#include "ShowAlgo.h"

vector<vector<vector<int>>> power_network_build_steps(N, vector<vector<int>>(N, vector<int>(N, 0)));
vector<vector<vector<int>>> DC_network_build_steps(N, vector<vector<int>>(N, vector<int>(N, 0)));

/************************ To graph ******************************************/
vector<vector<vector<int>>> start_MST_build_power_network(){ //vector of graphs (Building the MST of power network)
    vector<vector<int>>powerEdges= makeEdgeList(modified_power_network); //construct the edge list for the power network
    kruskalMST(N,powerEdges,power_network_build_steps);    //find the MST for the power network with each step
    return power_network_build_steps;
}

vector<vector<vector<int>>> start_MST_build_DC_network(){   //vector of graphs (Building the MST of DC network)
    vector<vector<int>>DCEdges= makeEdgeList(modified_DC_network); //construct the edge list for the DC network
    kruskalMST(N,DCEdges,DC_network_build_steps);   //find the MST for the DC network with each step
    return DC_network_build_steps;
}
/*************************************************************************/

vector<int> start_shortest_path(int source, int goal){
    int shortest_path;
    vector<int> route;

    A_Star(modified_road_network, source, goal, shortest_path, route);

    return route;
}

///////////////// Ford Fulkerson ////////////////////////
int printFord::get_source() {
    return source;
}
int printFord::get_sink() {
    return sink;
}
int printFord::get_max_flow() {
    return maxflow;
}
vector<vector<int> > printFord::get_cap() {
    return cap;
}
vector<vector<int > > printFord::get_flow() {
    return flow;
}
printFord start_ford_fulkerson(vector<vector<int> > cap,int source,int sink){
    printFord toreturn;
    toreturn.source=source;
    toreturn.sink= sink;
    toreturn.cap=cap;
    toreturn.maxflow= ford_fulkerson(cap,source, sink).second;
    toreturn.flow= ford_fulkerson(cap,source, sink).first;
    return toreturn;
}
/////////////////// Restart Function //////////////////////
void boomboom(){
    modified_road_network_capacity=road_network_capacity;
    modified_DC_network_capacity=DC_network_capacity;
    modified_power_network_capacity=power_network_capacity;
    modified_road_network=road_network;
    modified_DC_network=DC_network;
    modified_power_network=power_network;
}