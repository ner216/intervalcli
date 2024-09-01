cmake_minimum_required(VERSION 3.25.1)
project(intervalcli)

add_executable(${PROJECT_NAME} Config.cpp Clock.cpp interval.cpp main.cpp)
add_subdirectory(Libraries)
target_link_libraries(${PROJECT_NAME} ConvertLib)
