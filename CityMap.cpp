#include <iostream>
#include <vector>
#include "CityMap.h"

//                                   {00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16}
vector<vector<int>> road_network =  {{00, 12, 00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 00, 00, 11, 00, 00}, // 0
                                     {12, 00, 10, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 15, 00}, // 1
                                     {00, 10, 00, 11, 00, 00, 00, 00, 00, 00, 00, 00, 00, 18,  9, 12, 00}, // 2
                                     {00, 00, 11, 00,  7, 00, 00,  8, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 3
                                     {00, 00, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 13, 00, 00}, // 4
                                     {00, 00, 00, 00, 00, 00, 12, 12, 00, 00, 00, 00, 11, 00, 00, 00, 11}, // 5
                                     {00, 00, 00, 00, 00, 12, 00, 00, 00, 00,  7, 00,  8, 00, 00, 00, 00}, // 6
                                     {00, 00, 00,  8, 00, 12, 00, 00, 00,  9, 00, 00, 00, 13, 00, 00,  7}, // 7
                                     {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 00}, // 8
                                     {00, 00, 00, 00, 00, 00, 00,  9, 00, 00, 00, 00, 00, 10, 00, 00, 00}, // 9
                                     {00, 00, 00, 00, 00, 00,  7, 00, 00, 00, 00, 10, 00, 00, 00, 00, 00}, // 10
                                     { 8, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 00, 00, 00, 10, 00, 00}, // 11
                                     {00, 00, 00, 00, 00, 11,  8, 00, 00, 00, 00, 00, 00, 00,  8, 00, 00}, // 12
                                     {00, 00, 18, 00, 00, 00, 00, 13, 00, 10, 00, 00, 00, 00, 00, 10, 00}, // 13
                                     {11, 10,  9, 00, 13, 00, 00, 00, 00, 00, 00, 10,  8, 00, 00, 00, 00}, // 14
                                     {00, 15, 12, 00, 00, 00, 00, 00,  8, 00, 00, 00, 00, 10, 00, 00, 00}, // 15
                                     {00, 00, 00, 00, 00, 11, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 16
};


//                                   {00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16}
vector<vector<int>> power_network = {{00, 12, 00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 00, 00, 11, 00, 00}, // 0
                                     {12, 00, 10, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 15, 00}, // 1
                                     {00, 10, 00, 11, 00, 00, 00, 00, 00, 00, 00, 00, 00, 18,  9, 12, 00}, // 2
                                     {00, 00, 11, 00,  7, 00, 00,  8, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 3
                                     {00, 00, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 13, 00, 00}, // 4
                                     {00, 00, 00, 00, 00, 00, 12, 12, 00, 00, 00, 00, 11, 00, 00, 00, 11}, // 5
                                     {00, 00, 00, 00, 00, 12, 00, 00, 00, 00,  7, 00,  8, 00, 00, 00, 00}, // 6
                                     {00, 00, 00,  8, 00, 12, 00, 00, 00,  9, 00, 00, 00, 13, 00, 00,  7}, // 7
                                     {00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 10, 00, 00, 00, 00,  8, 00}, // 8
                                     {00, 00, 00, 00, 00, 00, 00,  9,  8, 00,  9, 00, 00, 10, 00, 00, 00}, // 9
                                     {00, 00, 00, 00, 00, 00,  7, 00, 10,  9, 00, 10, 00, 00, 00, 00, 00}, // 10
                                     { 8, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 00, 00, 00, 10, 00, 00}, // 11
                                     {00, 00, 00, 00, 00, 11,  8, 00, 00, 00, 00, 00, 00, 00,  8, 00, 00}, // 12
                                     {00, 00, 18, 00, 00, 00, 00, 13, 00, 10, 00, 00, 00, 00, 00, 10, 00}, // 13
                                     {11, 10,  9, 00, 13, 00, 00, 00, 00, 00, 00, 10,  8, 00, 00, 00, 00}, // 14
                                     {00, 15, 12, 00, 00, 00, 00, 00,  8, 00, 00, 00, 00, 10, 00, 00, 00}, // 15
                                     {00, 00, 00, 00, 00, 11, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 16
};


//                                {00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16}
vector<vector<int>> DC_network = {{00, 12, 00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 00, 00, 11, 00, 00}, // 0
                                  {12, 00, 10, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 15, 00}, // 1
                                  {00, 10, 00, 11, 00, 00, 00, 00, 00, 00, 00, 00, 00, 18,  9, 12, 00}, // 2
                                  {00, 00, 11, 00,  7, 00, 00,  8, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 3
                                  {00, 00, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 13, 00, 00}, // 4
                                  {00, 00, 00, 00, 00, 00, 12, 12, 00, 00, 00, 00, 11, 00, 00, 00, 11}, // 5
                                  {00, 00, 00, 00, 00, 12, 00, 00, 00, 00,  7, 00,  8, 00, 00, 00, 00}, // 6
                                  {00, 00, 00,  8, 00, 12, 00, 00, 00,  9, 00, 00, 00, 13, 00, 00,  7}, // 7
                                  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,  8, 00}, // 8
                                  {00, 00, 00, 00, 00, 00, 00,  9, 00, 00, 00, 00, 00, 10, 00, 00, 00}, // 9
                                  {00, 00, 00, 00, 00, 00,  7, 00, 00, 00, 00, 10, 00, 00, 00, 00, 00}, // 10
                                  { 8, 00, 00, 00, 00, 00, 00, 00, 00, 00, 10, 00, 12, 00, 10, 00, 00}, // 11
                                  {00, 00, 00, 00, 00, 11,  8, 00, 00, 00, 00, 12, 00, 16,  8, 00, 00}, // 12
                                  {00, 00, 18, 00, 00, 00, 00, 13, 00, 10, 00, 00, 16, 00, 00, 10, 00}, // 13
                                  {11, 10,  9, 00, 13, 00, 00, 00, 00, 00, 00, 10,  8, 00, 00, 00, 00}, // 14
                                  {00, 15, 12, 00, 00, 00, 00, 00,  8, 00, 00, 00, 00, 10, 00, 00, 00}, // 15
                                  {00, 00, 00, 00, 00, 11, 00,  7, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 16
};

vector<vector<int>> road_network_capacity = {
        //{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16}
        {0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 4, 0, 0},// 0
        {6, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 0},// 1
        {0, 10, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 6, 0},// 2
        {0, 0, 6, 0, 10, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},// 3
        {0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},// 4
        {0, 0, 0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 9, 0, 0, 0, 4},// 5
        {0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 9, 0, 10, 0, 0, 0, 0},// 6
        {0, 0, 0, 6, 0, 4, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 3},// 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},// 8
        {0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 7, 0, 0, 0},// 9
        {0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0},// 10
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 8, 0, 0},// 11
        {0, 0, 0, 0, 0, 9, 10, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0},// 12
        {0, 0, 2, 0, 0, 0, 0, 8, 0, 7, 0, 0, 0, 0, 0, 7, 0},// 13
        {4, 8, 10, 0, 7, 0, 0, 0, 0, 0, 0, 8, 5, 0, 0, 0, 0},// 14
        {0, 10, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 7, 0, 0, 0},// 15
        {0, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}// 16
};
vector<vector<int>> power_network_capacity = {
      //{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16}
        {0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 4, 0, 0},// 0
        {6, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 0},// 1
        {0, 10, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 6, 0},// 2
        {0, 0, 6, 0, 10, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},// 3
        {0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},// 4
        {0, 0, 0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 9, 0, 0, 0, 4},// 5
        {0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 9, 0, 10, 0, 0, 0, 0},// 6
        {0, 0, 0, 6, 0, 4, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 3},// 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 0, 0, 0, 0, 5, 0},// 8
        {0, 0, 0, 0, 0, 0, 0, 5, 6, 0, 8, 0, 0, 7, 0, 0, 0},// 9
        {0, 0, 0, 0, 0, 0, 9, 0, 3, 8, 0, 10, 0, 0, 0, 0, 0},// 10
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 8, 0, 0},// 11
        {0, 0, 0, 0, 0, 9, 10, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0},// 12
        {0, 0, 2, 0, 0, 0, 0, 8, 0, 7, 0, 0, 0, 0, 0, 7, 0},// 13
        {4, 8, 10, 0, 7, 0, 0, 0, 0, 0, 0, 8, 5, 0, 0, 0, 0},// 14
        {0, 10, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 7, 0, 0, 0},// 15
        {0, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}// 16
};
vector<vector<int>> DC_network_capacity = {
      //{0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16}
        {0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 4, 0, 0},// 0
        {6, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 0},// 1
        {0, 10, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 6, 0},// 2
        {0, 0, 6, 0, 10, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},// 3
        {0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},// 4
        {0, 0, 0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 9, 0, 0, 0, 4},// 5
        {0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 9, 0, 10, 0, 0, 0, 0},// 6
        {0, 0, 0, 6, 0, 4, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 3},// 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},// 8
        {0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 7, 0, 0, 0},// 9
        {0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0},// 10
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 7, 0, 8, 0, 0},// 11
        {0, 0, 0, 0, 0, 9, 10, 0, 0, 0, 0, 7, 0, 4, 5, 0, 0},// 12
        {0, 0, 2, 0, 0, 0, 0, 8, 0, 7, 0, 0, 4, 0, 0, 7, 0},// 13
        {4, 8, 10, 0, 7, 0, 0, 0, 0, 0, 0, 8, 5, 0, 0, 0, 0},// 14
        {0, 10, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 7, 0, 0, 0},// 15
        {0, 0, 0, 0, 0, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}// 16
};



vector<coordinate> City_coordinates = {{0,     -13.97},   // 0
                                       {8.63,  -18.41},   // 1
                                       {13.34, -12.06},   // 2
                                       {21.59, -9.84},    // 3
                                       {16.83, -7.62},    // 4
                                       {18.73, -4.13},    // 5
                                       {9.21,  -0.63 },   // 6
                                       {26.99, -8.57},    // 7
                                       {19.05, -21.91},   // 8
                                       {33.34, -10.16},   // 9
                                       {4.45,  -1.59},    // 10
                                       {0,     -7.94},    // 11
                                       {10.48, -6.35},    // 12
                                       {28.89, -15.87},   // 13
                                       {6.99,  -11.11},    // 14
                                       {21.27, -17.78},   // 15
                                       {26.99, -4.13}     // 16
};


int getEdges(vector<vector<int>> &graph, int node){
    int edges = 0;
    for(int i = 0; i < N; i++){
        if(graph[node][i] != 0)
            edges++;
    }
    return edges;
}

std::vector<std::vector<int>> get_road_network() {
    return road_network;
}

// Function to return city coordinates
std::vector<coordinate> get_city_coordinates() {
    return City_coordinates;
}

