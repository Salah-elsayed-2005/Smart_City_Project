from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "smart_city",
        [
            "../bindings.cpp",
            "../CityMap.cpp",
            "../FordFulkerson.cpp",
            "../MST.cpp",
            "../A_star.cpp",
            "../EventHandler.cpp",
            "../ShowAlgo.cpp"
        ],
        include_dirs=["../include"],  # Adjust paths as needed
    ),
]

setup(
    name="smart_city",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
