add_executable(asafe src/control.cpp src/main.cpp src/persistence.cpp)

target_include_directories(asafe 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	        ${PROJECT_SOURCE_DIR}/commons/include	
                ${PROJECT_SOURCE_DIR}/web/include)

target_link_libraries(asafe web commons)


add_executable(app_test src/control.cpp
			src/persistence.cpp
			test/persistence.cpp
			test/test_runner.cpp)

target_include_directories(app_test
    PRIVATE /usr/include/catch2
            ${CMAKE_CURRENT_SOURCE_DIR}/include
	    ${PROJECT_SOURCE_DIR}/commons/include	
            ${PROJECT_SOURCE_DIR}/web/include)

target_link_libraries(app_test commons web)

add_test(NAME app_test
         COMMAND app_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
 
install(TARGETS asafe RUNTIME DESTINATION /usr/bin)
install(FILES data/00-asafe.hook DESTINATION /etc/pacman.d/hooks)
install(FILES data/mode data/time 
	DESTINATION /usr/share/asafe/
	PERMISSIONS WORLD_READ OWNER_WRITE)

