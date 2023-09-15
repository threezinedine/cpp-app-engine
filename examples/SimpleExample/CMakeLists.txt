project(
    SimpleExample
)

file(
    GLOB
    SIMPLE_EXAMPLE_SRC_FILES
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SIMPLE_EXAMPLE_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCore
)