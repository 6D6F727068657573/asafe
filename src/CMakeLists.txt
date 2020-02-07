cmake_minimum_required(VERSION 3.5)

project(arch_updater
    VERSION 1.0
    DESCRIPTION "A lightway tool for performaning safe updates."
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(commons)
add_subdirectory(system)
add_subdirectory(web)
add_subdirectory(app)
