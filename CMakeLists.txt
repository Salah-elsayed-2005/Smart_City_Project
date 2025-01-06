cmake_minimum_required(VERSION 3.10)
project(Smart_City_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find pybind11 package
find_package(pybind11 REQUIRED)

# Create a pybind11 module (Python bindings)
pybind11_add_module(SmartCityModule main.cpp)

# Add executable for the main project
add_executable(Smart_City_Project main.cpp
        MST.cpp
        EventHandler.cpp
        A_star.cpp
        CityMap.cpp
        FordFulkerson.cpp
        bindings.cpp
        ShowAlgo.cpp
)

# Include directories
target_include_directories(Smart_City_Project PRIVATE include)

# Add dependencies
target_link_libraries(Smart_City_Project PRIVATE pybind11::module)
