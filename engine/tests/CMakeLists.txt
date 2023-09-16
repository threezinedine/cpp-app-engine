project(
    EngineCoreTesting
)


file(
    GLOB
    ENGINE_CORE_TESTING_SRC_FILES
    ./*.cpp
)


SET(TEST_FOLDERS
    ../src/modules/EngineImGui/tests
    ../src/modules/EngineApplication/tests
    ../src/modules/EngineDataType/tests
)

foreach(folder ${TEST_FOLDERS})
    file(
        GLOB
        CPP_FILES_IN_FOLDER
        ${folder}/*.cpp
    ) 

    list(APPEND ENGINE_CORE_TESTING_SRC_FILES ${CPP_FILES_IN_FOLDER})
endforeach()

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