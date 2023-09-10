project(
    EngineExceptions
)

file(
    GLOB
    ENGINE_EXCEPTIONS_SRC_FILES
    ./*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${ENGINE_EXCEPTIONS_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)