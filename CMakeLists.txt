cmake_minimum_required(VERSION 3.10)

project(
    AppEngine
    VERSION 1.0.1
)

find_package(OpenCV REQUIRED 
                PATHS C:/Users/Acer/C_Language/C++/CPlusPlusLibs/opencv/build)

add_subdirectory(./engine)
add_subdirectory(./examples)