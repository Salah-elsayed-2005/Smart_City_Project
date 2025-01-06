#include <iostream>
#include <vector>
#include "CityMap.h"
#include "A_Star.h"
#include "MST.h"
#include "FordFulkerson.h"
#include "EventHandler.h"

#include "ShowAlgo.h"

vector<vector<vector<int>>> start_MST_build_power_network(){

}
vector<vector<vector<int>>> start_MST_build_DC_network(){

}


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
vector<vector<int > > printFord::get_cap() {
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

}