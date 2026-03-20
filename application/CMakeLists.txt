cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerApplication)

set(PROJECT_APPLICATION_NAME TreeVisualizerApplication)
set(APPLICATION_CORE_TARGET_NAME TreeVisualizerCore)



set(PROJECT_SOURCES
entry_point.cpp
)

set(PROJECT_HEADERS
)

set(PROJECT_DEPENDENCY_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../vendor")
set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../")

add_executable(${PROJECT_APPLICATION_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_target_properties(${PROJECT_APPLICATION_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/" "${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/build")
add_subdirectory("${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/" "${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/local_build")
add_subdirectory("${PROJECT_ROOT}/core/src" "${PROJECT_ROOT}/build/core")


target_compile_definitions(${PROJECT_APPLICATION_NAME} PRIVATE GLEW_STATIC)


target_include_directories(${PROJECT_APPLICATION_NAME} PUBLIC 
	"${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/include"
	"${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/include"
)

target_link_directories(${PROJECT_APPLICATION_NAME} PUBLIC

	"${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/local_build/lib/Debug"
	"${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/build/src/Debug"
	"${PROJECT_ROOT}/build/build/core/Debug"
)

target_link_libraries(${PROJECT_APPLICATION_NAME}
	PUBLIC opengl32
   "$<$<CONFIG:Debug>:glfw3.lib>"
	
   "$<$<CONFIG:Debug>:glewd.lib>"

   	${APPLICATION_CORE_TARGET_NAME}

)
add_dependencies(${PROJECT_APPLICATION_NAME} glfw libglew_static TreeVisualizerCore)

