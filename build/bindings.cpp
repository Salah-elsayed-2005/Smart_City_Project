#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ShowAlgo.h"
#include "EventHandler.h"
#include "CityMap.h"

namespace py = pybind11;

// Convert coordinates to a Python-friendly format
std::vector<std::pair<float, float>> get_city_coordinates_python() {
    std::vector<std::pair<float, float>> python_coords;
    for (const auto& coord : City_coordinates) {
        python_coords.emplace_back(coord.x, coord.y);
    }
    return python_coords;
}


PYBIND11_MODULE(smart_city, m) {
    m.doc() = "Smart City Simulation Module";

    // Expose road network
    m.def("get_road_network", &get_road_network, "Get the road network as a list of lists");

    // Expose city coordinates
    m.def("get_city_coordinates", &get_city_coordinates_python, "Get city coordinates as a list of (x, y) pairs");


    // Expose individual algorithms
    m.def("ford_fulkerson", &ford_fulkerson, "Run the Ford-Fulkerson algorithm",
          py::arg("graph"), py::arg("source"), py::arg("sink"));


    py::class_<Event, std::shared_ptr<Event>>(m, "Event")
            .def("trigger", &Event::trigger)
            .def("handle", &Event::handle);

    // Expose event handling classes
    py::class_<Earthquake, Event, std::shared_ptr<Earthquake>>(m, "Earthquake")            .def(py::init<int>())
            .def("trigger", &Earthquake::trigger) // call this
            .def("handle", &Earthquake::handle)

            .def("get_road_network_trigger_steps", &Earthquake::get_road_network_trigger_steps) //steps for road
            .def("get_power_network_trigger_steps", &Earthquake::get_power_network_trigger_steps) //steps for pow
            .def("get_DC_network_trigger_steps", &Earthquake::get_DC_network_trigger_steps) //steps for dc

            .def("get_power_network_handle_steps", &Earthquake::get_power_network_handle_steps) // steps building for pow
            .def("get_DC_network_handle_steps", &Earthquake::get_DC_network_handle_steps) // steps building for dc

            .def("get_emergency_routes", &Earthquake::get_emergency_routes); // 3 steps


            //SAME ^
    py::class_<Maintenance, Event, std::shared_ptr<Maintenance>>(m, "Maintenance")
            .def(py::init<int>())
            .def("trigger", &Maintenance::trigger)
            .def("handle", &Maintenance::handle)

            .def("get_power_network_trigger_steps", &Maintenance::get_power_network_trigger_steps)
            .def("get_DC_network_trigger_steps", &Maintenance::get_DC_network_trigger_steps)

            .def("get_power_network_handle_steps", &Maintenance::get_power_network_handle_steps)
            .def("get_DC_network_handle_steps", &Maintenance::get_DC_network_handle_steps);


    py::class_<TrafficCongestion, Event, std::shared_ptr<TrafficCongestion>>(m, "TrafficCongestion")
            .def(py::init<int>())
            .def("trigger", &TrafficCongestion::trigger)
            .def("handle", &TrafficCongestion::handle);

    // Expose ShowAlgo functions
    m.def("start_MST_build_power_network", &start_MST_build_power_network, "Build MST for the power network");

    m.def("start_MST_build_DC_network", &start_MST_build_DC_network, "Build MST for the DC network");

    m.def("start_shortest_path", &start_shortest_path, "Find the shortest path using A* algorithm",
          py::arg("source"), py::arg("goal"));

    // Expose Ford-Fulkerson results wrapper
    py::class_<printFord>(m, "PrintFord")
            .def("get_cap", &printFord::get_cap)
            .def("get_flow", &printFord::get_flow)
            .def("get_max_flow", &printFord::get_max_flow)
            .def("get_source", &printFord::get_source)
            .def("get_sink", &printFord::get_sink);

    m.def("start_ford_fulkerson", &start_ford_fulkerson, "Run and return results of Ford-Fulkerson algorithm",
          py::arg("cap"), py::arg("source"), py::arg("sink"));
}
