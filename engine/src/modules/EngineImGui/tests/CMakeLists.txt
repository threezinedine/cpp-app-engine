project(
    EngineImguiTest
)

file(
    GLOB
    ENGINE_IMGUI_TEST_SRC_FILES
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${ENGINE_IMGUI_TEST_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ./
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    gtest
    gmock
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    EngineImGui
)