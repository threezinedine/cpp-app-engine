project(
    EngineWindow
)

file(
    GLOB
    ENGINE_WINDOW_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_WINDOW_SRC_FILES}
)

find_package(OpenGL REQUIRED)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCores
    gtest
    gmock
    glfw
    OpenGL::GL
    ImGui
)