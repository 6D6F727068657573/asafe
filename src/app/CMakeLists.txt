add_executable(asafe src/main.cpp)
target_link_libraries(asafe web commons system)

install(TARGETS asafe RUNTIME DESTINATION bin)
install(FILES data/asafe.hook DESTINATION /etc/pacman.d/hooks)
