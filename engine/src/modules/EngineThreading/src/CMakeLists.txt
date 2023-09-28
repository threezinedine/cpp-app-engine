project(
    EngineThreading
)


file(GLOB
    ENGINE_THREADING_SRC_FILES
    ./*.cpp
)


add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_THREADING_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCores
    EngineDataType
)