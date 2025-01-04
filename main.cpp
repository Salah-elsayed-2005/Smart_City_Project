#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "FordFulkerson.h"
#include "MST.h"
#include <vector>
#include <iostream>

namespace py = pybind11;

PYBIND11_MODULE(scpalgo, m) {
    // Ford-Fulkerson State Binding
    py::class_<State>(m, "State")
            .def_readwrite("residualGraph", &State::residualGraph)
            .def_readwrite("visited", &State::visited)
            .def_readwrite("exploredEdges", &State::exploredEdges);

    // MST State Binding
    py::class_<MSTState>(m, "MSTState")
            .def_readwrite("mstEdges", &MSTState::mstEdges);

    // Ford-Fulkerson Function Binding
    m.def("ford_fulkerson", &ford_fulkerson, "Run the Ford-Fulkerson algorithm",
          py::arg("capacity"), py::arg("source"), py::arg("sink"));

    // Kruskal MST Function Binding
    m.def("kruskal_mst", &kruskalMST, "Run Kruskal's MST algorithm",
          py::arg("n"), py::arg("edges"));
}

int main() {
    // Example Usage for Testing
    std::vector<std::vector<int>> capacities = {
            {0, 10, 10, 0, 0, 0},
            {0, 0, 0, 4, 8, 0},
            {0, 0, 0, 0, 9, 10},
            {0, 0, 0, 0, 0, 10},
            {0, 0, 0, 6, 0, 10},
            {0, 0, 0, 0, 0, 0}
    };

    int source = 0, sink = 5;
    std::vector<State> ff_states = ford_fulkerson(capacities, source, sink);

    for (const auto &state : ff_states) {
        std::cout << "Residual Graph: \n";
        for (const auto &row : state.residualGraph) {
            for (int cap : row) {
                std::cout << cap << " ";
            }
            std::cout << "\n";
        }
        std::cout << "Visited Nodes: \n";
        for (bool visited : state.visited) {
            std::cout << visited << " ";
        }
        std::cout << "\nExplored Edges: \n";
        for (const auto &edge : state.exploredEdges) {
            std::cout << edge.first << "->" << edge.second << " ";
        }
        std::cout << "\n------------------\n";
    }

    std::vector<std::vector<int>> edges = {
            {0, 1, 10},
            {1, 2, 5},
            {2, 3, 8},
            {3, 4, 12},
            {4, 1, 7}
    };

    std::vector<MSTState> mst_states = kruskalMST(5, edges);

    for (const auto &state : mst_states) {
        std::cout << "MST Edges: \n";
        for (const auto &edge : state.mstEdges) {
            std::cout << edge.first << "--" << edge.second << " ";
        }
        std::cout << "\n------------------\n";
    }

    return 0;
}