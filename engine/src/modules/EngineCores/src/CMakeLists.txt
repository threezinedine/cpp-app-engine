project(
    EngineCores
)

file(
    GLOB
    ENGINE_CORES_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_CORES_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)