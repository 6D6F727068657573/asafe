
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/http.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/announce.cpp)

add_library(web SHARED ${SOURCES})

target_include_directories(web
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE /usr/include/curl/
            ${PROJECT_SOURCE_DIR}/commons/include)

target_link_libraries(web -lcurl commons)


add_executable(web_test ${CMAKE_CURRENT_SOURCE_DIR}/test/announce.cpp
                                  ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runner.cpp)

target_include_directories(web_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/commons/include)

target_link_libraries(web_test commons web)
add_test(NAME web_test
        COMMAND web_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
