add_executable(asafe src/main.cpp)
target_link_libraries(asafe web commons system)

install(TARGETS asafe RUNTIME DESTINATION /usr/bin)
install(FILES data/00-asafe.hook DESTINATION /etc/pacman.d/hooks)
install(FILES data/mode DESTINATION /usr/share/asafe/)
