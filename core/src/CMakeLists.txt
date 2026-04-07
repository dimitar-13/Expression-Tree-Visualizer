cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerCore)

set(PROJECT_NAME TreeVisualizerCore)
set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../")

set(PROJECT_SOURCES 
    main.cpp
    ExpressionTree.cpp
    ExpressionTreeBuilder.cpp
	ExpressionValidator.cpp
)

set(PROJECT_HEADERS 
     ${PROJECT_ROOT}/include/structs/TreeNode.h
     ${PROJECT_ROOT}/include/ExpressionTree.h
     ${PROJECT_ROOT}/include/ExpressionTreeBuilder.h
	 ${PROJECT_ROOT}/include/ExpressionValidator.h
     helpers/ExpressionConverter.h
     States/StateRecordable.h
     States/StateManager.h
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC 
	 ${PROJECT_ROOT}/include
	 ${PROJECT_ROOT}/src
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)