project(
    EngineApplicationTest
)

file(
    GLOB
    ENGINE_APPLICATION_TEST_SRC_FILES
    ./*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${ENGINE_APPLICATION_TEST_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}    
    PRIVATE
    gtest
    gmock
)

target_link_libraries(
    ${PROJECT_NAME}    
    PUBLIC
    EngineCores
    EngineApplication
    EngineExceptions
    EngineWindow
)