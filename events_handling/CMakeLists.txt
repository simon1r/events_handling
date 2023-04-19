cmake_minimum_required(VERSION 3.5)

project(events_handling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(events_handling main.cpp)

install(TARGETS events_handling
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
