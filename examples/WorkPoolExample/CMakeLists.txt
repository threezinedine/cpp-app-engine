project(
    WorkPoolExample
)

file(GLOB
    WORK_POOL_EXAMPLE_SRC_FILES 
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${WORK_POOL_EXAMPLE_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCore
)