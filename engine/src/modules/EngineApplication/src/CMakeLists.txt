project(
    EngineApplication
)

file(
    GLOB
    ENGINE_APPLICATION_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_APPLICATION_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineWindow
    EngineExceptions
)