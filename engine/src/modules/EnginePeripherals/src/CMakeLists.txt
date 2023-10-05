project(
    EnginePeripherals
)

file(GLOB
    ENGINE_PERIPHERALS_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_PERIPHERALS_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ImGui
    EngineCores
    EngineDataType
    EngineThreading
)