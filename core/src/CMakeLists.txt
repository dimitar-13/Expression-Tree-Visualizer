cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerCore)

set(PROJECT_NAME TreeVisualizerCore)

set(PROJECT_SOURCES 
    main.cpp
    ExpressionTree.cpp
    ExpressionTreeBuilder.cpp
)

set(PROJECT_HEADERS 
    structs/TreeNode.h
    ExpressionTree.h
    helpers/ExpressionConverter.h
    States/StateRecordable.h
    ExpressionTreeBuilder.h
    States/StateManager.h
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
