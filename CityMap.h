#ifndef CITY_MAP_H
#define CITY_MAP_H

//#include <iostream>
#include <vector>
using namespace std;


struct coordinate{
    float x;
    float y;
};

extern vector<vector<int>> road_network;
extern vector<vector<int>> power_network;
extern vector<vector<int>> DC_network;
extern vector<vector<int> > road_network_capacity;
extern vector<vector<int> > power_network_capacity;
extern vector<vector<int> > DC_network_capacity;
extern vector<coordinate> City_coordinates;


#endif