# Instructions to Build and Run the Project on Windows

## Prerequisites

1. **Install Python**
   - Download and install Python (3.8 or later) from [python.org](https://www.python.org/).
   - During installation, ensure you check the box **"Add Python to PATH"**.


2. **Install `pybind11`**
   - Open a terminal and install `pybind11` using pip:
     ```bash
     pip3 install pybind11
     ```

3. **Install Python Dependencies**
   - Use pip to install the required Python libraries:
     ```bash
     pip3 install dash plotly
     ```

---

## Setting Up the Project in CLion

1. **Clone or Download the Repository**
   - Clone the repository using Git or download the source files.

2. **Open the Project in CLion**
   - Launch CLion and click **Open**.
   - Navigate to the project folder and select it.

3. **Configure the `CMakeLists.txt`**
   - Ensure your `CMakeLists.txt` file is properly set up for the project:
     ```cmake
     cmake_minimum_required(VERSION 3.14)
     project(Smart_City_Project)

     set(CMAKE_CXX_STANDARD 17)

     find_package(Python3 REQUIRED COMPONENTS Development)
     find_package(pybind11 REQUIRED)

     include_directories(${CMAKE_SOURCE_DIR}/include)

     add_library(scpalgo MODULE main.cpp FordFulkerson.h MST.h)
     target_link_libraries(scpalgo PRIVATE pybind11::module)
     ```

4. **Configure the Python Environment in CLion**
   - Go to **File > Settings > Build, Execution, Deployment > Python Interpreter**.
   - Set the Python interpreter to the one installed on your system.
   - Ensure the required libraries (`dash`, `plotly`, `pybind11`) are installed.

5. **Set the Build Target**
   - Go to **File > Settings > Build, Execution, Deployment > CMake**.
   - Ensure the build target is set to `scp_algo`.
   - Choose the appropriate generator (e.g., **Visual Studio 2019**).

6. **Build the Project**
   - Click **Build > Build Project** to compile the project.
   - Ensure the `.pyd` file (`scp_algo.pyd`) is generated in the `cmake-build-release` or equivalent directory.

---

## Running the Python Script

1. **Verify the Python Module**
   - Check that the compiled `.pyd` file is in the same directory as the Python script or add its path to `PYTHONPATH`.

2. **Run the Python Visualization Script**
   - Navigate to the Python script (`app.py` or similar).
   - Run the script using Python:
     ```bash
     python app.py
     ```

3. **Access the Visualization**
   - Open your browser and navigate to the provided local server URL (e.g., `http://127.0.0.1:8050/`).

---

## Troubleshooting

1. **CMake Errors in CLion**
   - Ensure you selected the correct generator in CLion settings.
   - Confirm that the `CMakeLists.txt` file is properly configured.

2. **Missing `scp_algo.pyd`**
   - Ensure the build completes successfully without errors.
   - Check the output directory for the `.pyd` file.

3. **Python Import Errors**
   - If the Python script cannot find the `scp_algo` module, add the build directory to `PYTHONPATH`:
     ```python
     import sys
     sys.path.append("path_to_build_directory")
     import scpalgo
     ```

4. **Port Already in Use**
   - If the Dash app fails to start because the port is in use, modify the `app.run_server` line in the Python script:
     ```python
     app.run_server(debug=True, port=8051)
     ```
