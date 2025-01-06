#ifndef SMART_CITY_PROJECT_SHOWALGO_H
#define SMART_CITY_PROJECT_SHOWALGO_H
using namespace std;

//////////////////////// HUSSEIN
vector<vector<vector<int>>> start_MST_build_power_network();
vector<vector<vector<int>>> start_MST_build_DC_network();


vector<int> start_shortest_path(int source, int goal);

////////////////////// SALAH
class printFord {
public:
    int maxflow,source,sink;
    vector<vector<int> >cap;
    vector<vector<int> >flow;


    vector<vector<int> > get_cap();
    vector<vector<int> > get_flow();
    int get_max_flow();
    int get_source();
    int get_sink();

};
printFord start_ford_fulkerson(vector<vector<int> > cap,int source,int sink);

#endif //SMART_CITY_PROJECT_SHOWALGO_H
