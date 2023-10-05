project(
    EngineCore
)

add_subdirectory(./modules)

file(
    GLOB
    ENGINE_CORE_SRC_FILES
    ./cores/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_CORE_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./cores/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineApplication
    EngineImGui
    EngineWindow
    EngineExceptions
    EngineCores
    EngineDataType
    EngineImGuiComponents
    EngineThreading
    EngineSupportWindows
    EnginePeripherals
)