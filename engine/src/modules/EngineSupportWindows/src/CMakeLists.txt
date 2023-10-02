project(
    EngineSupportWindows
)


file(GLOB
    ENGINE_SUPPORT_WINDOWS_SRC_FILES
    ./*.cpp
)


add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_SUPPORT_WINDOWS_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineImGui
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)