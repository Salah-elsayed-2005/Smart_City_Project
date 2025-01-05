#ifndef SMART_CITY_PROJECT_EVENTHANDLER_H
#define SMART_CITY_PROJECT_EVENTHANDLER_H

using namespace std;

extern vector<vector<int>> modified_road_network;
extern vector<vector<int>> modified_power_network;
extern vector<vector<int>> modified_DC_network;
extern vector<vector<int>> modified_road_network_capacity;
extern vector<vector<int>> modified_power_network_capacity;
extern vector<vector<int>> modified_DC_network_capacity;

class Event {
public:
    int damaged_node;

    Event(int damaged_node) : damaged_node(damaged_node) {}

    virtual void trigger() = 0;
    virtual void handle() = 0;

};

class Earthquake : public Event {
public:
    Earthquake(int damaged_node) : Event(damaged_node) {}

    void trigger();
    void handle();

};

class Maintenance : public Event {
    Maintenance(int damaged_node) : Event(damaged_node) {}

    void trigger();
    void handle();
};

class TrafficCongestion : public Event {
    TrafficCongestion(int damaged_node) : Event(damaged_node) {}

    void trigger();
    void handle();
};


#endif //SMART_CITY_PROJECT_EVENTHANDLER_H
