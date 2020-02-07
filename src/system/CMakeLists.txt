
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/pacman.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/mode.cpp)

add_library(system STATIC ${SOURCES})

target_include_directories(system
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/commons/include)

target_link_libraries(system commons)


add_executable(system_test  ${CMAKE_CURRENT_SOURCE_DIR}/test/pacman.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/test/mode.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runner.cpp)

target_include_directories(system_test
    PRIVATE /usr/include/catch2
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/commons/include)

target_link_libraries(system_test commons system)

add_test(NAME system_test
        COMMAND system_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
