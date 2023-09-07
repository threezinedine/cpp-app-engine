cmake_minimum_required(VERSION 3.10)

project(
    AppEngine
    PROJECT_DESCRIPTION Use for developing ImGui Fast
    VERSION 1.0.1
)

add_subdirectory(
    ./engine
    ./examples
    ./tests
)