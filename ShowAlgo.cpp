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