set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/logging.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp)

    add_library(commons STATIC ${SOURCES})
target_include_directories(commons PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(commons_test ${CMAKE_CURRENT_SOURCE_DIR}/test/logging.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/test/utils.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runner.cpp)

target_include_directories(commons_test
    PRIVATE /usr/include/catch2
            ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(commons_test commons)

add_test(NAME commons_test
        COMMAND commons_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
