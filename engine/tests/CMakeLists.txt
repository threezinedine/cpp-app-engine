project(
    EngineCoreTesting
)

file(
    GLOB
    ENGINE_CORE_TESTING_SRC_FILES
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${ENGINE_CORE_TESTING_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE 
    ./
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    gtest
    gmock
    EngineCore
)