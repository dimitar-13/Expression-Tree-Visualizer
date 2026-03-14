cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerCore)
set(PROJECT_NAME,"TreeVisualizerCore")
add_executable(${PROJECT_NAME} src/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
