#ifndef SMART_CITY_PROJECT_A_STAR_H
#define SMART_CITY_PROJECT_A_STAR_H

using namespace std;

int HeuristicValue(vector<vector<int>> &graph, int source, int goal);
void A_Star(vector<vector<int>> &graph, int source, int goal, int &shortest_path, vector<int> &route);


#endif //SMART_CITY_PROJECT_A_STAR_H
