cmake_minimum_required(VERSION 3.16)

project(test_hello LANGUAGES C)

add_executable(test_hello main.c)

include(GNUInstallDirs)
install(TARGETS test_hello
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
