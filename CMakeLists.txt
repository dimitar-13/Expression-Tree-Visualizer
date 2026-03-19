cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerCore)

set(PROJECT_NAME TreeVisualizerCore)

set(PROJECT_SOURCES 
    src/main.cpp
    src/ExpressionTree.cpp
    src/ExpressionTreeBuilder.cpp
)

set(PROJECT_HEADERS 
    src/structs/TreeNode.h
    src/ExpressionTree.h
    src/helpers/ExpressionConverter.h
    src/States/StateRecordable.h
    src/ExpressionTreeBuilder.h
    src/States/StateManager.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
