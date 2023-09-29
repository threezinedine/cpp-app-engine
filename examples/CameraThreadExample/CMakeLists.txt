project(
    CameraThreadExample
)

file(GLOB
    CAMERA_THREAD_EXAMPLE_SRC_FILES
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${CAMERA_THREAD_EXAMPLE_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    EngineCore
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ./include
)