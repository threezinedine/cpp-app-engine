project(
    EngineDataType
)

file(
    GLOB
    ENGINE_DATA_TYPE_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_DATA_TYPE_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCores
    ImGui
    EngineImGuiComponents
    ConfigurationCppLibs
    ${OpenCV_LIBS}
)