cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerCore)
set(PROJECT_NAME,"TreeVisualizerCore")

set(PROJECT_SOURCES src/main.cpp src/ExpressionTree.cpp)
set(PROJECT_HEADERS src/TreeNode.h src/ExpressionTree.h "src/helpers/ExpressionConverter.h" )

add_executable(${PROJECT_NAME}  ${PROJECT_SOURCES} ${PROJECT_HEADERS} "src/ExpressionTree.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
