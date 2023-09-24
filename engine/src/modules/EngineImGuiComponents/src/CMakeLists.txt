project(
    EngineImGuiComponents
)


file(
    GLOB
    ENGINE_IMGUI_COMPONENTS_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_IMGUI_COMPONENTS_SRC_FILES}
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
    EngineDataType
)