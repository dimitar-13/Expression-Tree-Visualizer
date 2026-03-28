cmake_minimum_required(VERSION 3.10)

project(TreeVisualizerApplication)

set(PROJECT_APPLICATION_NAME TreeVisualizerApplication)
set(APPLICATION_CORE_TARGET_NAME TreeVisualizerCore)

set(PROJECT_DEPENDENCY_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../vendor")
set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../")


set(IMGUI_SORUCES
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/backends/imgui_impl_opengl3.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/backends/imgui_impl_opengl3.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/backends/imgui_impl_glfw.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/backends/imgui_impl_glfw.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui_demo.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui_draw.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui_internal.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui_tables.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui_widgets.cpp
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imstb_rectpack.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imstb_textedit.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imstb_truetype.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imconfig.h
	${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui/imgui.cpp
)



set(PROJECT_SOURCES
	entry_point.cpp
	src/window_class.cpp
	src/application.cpp
	src/layers/ui_layer.cpp
	src/layers/graphics_layer.cpp
	src/graphics/shader_class.cpp
	src/graphics/batch_renderer.cpp
)
source_group("src/" FILES ${PROJECT_SOURCES} )

set(PROJECT_HEADERS
	src/window_class.h
	src/application.h
	src/layers/graphics_layer.h
	src/layers/layer.h
	src/layers/ui_layer.h
	src/graphics/shader_class.h
	src/graphics/batch_renderer.h
	src/helpers/treeSymmetryEnum.h
)

add_executable(${PROJECT_APPLICATION_NAME} ${PROJECT_SOURCES} ${IMGUI_SORUCES} ${PROJECT_HEADERS})

source_group("imgui/" FILES ${IMGUI_SORUCES} )

set_target_properties(${PROJECT_APPLICATION_NAME} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/" "${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/build")
add_subdirectory("${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/" "${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/local_build")
add_subdirectory("${PROJECT_DEPENDENCY_FOLDER}/glm/glm/" "${PROJECT_DEPENDENCY_FOLDER}/glm/glm/local_build")
add_subdirectory("${PROJECT_ROOT}/core/src" "${PROJECT_ROOT}/build/core")


target_compile_definitions(${PROJECT_APPLICATION_NAME} PRIVATE GLEW_STATIC)


target_include_directories(${PROJECT_APPLICATION_NAME} PUBLIC 
	"${PROJECT_DEPENDENCY_FOLDER}/glfw/glfw/include"
	"${PROJECT_DEPENDENCY_FOLDER}/glew/glew-cmake/include"
	"${PROJECT_DEPENDENCY_FOLDER}/glm/glm/"
	 ${PROJECT_DEPENDENCY_FOLDER}/imgui/imgui
	 ${PROJECT_ROOT}/application/src
	 ${PROJECT_ROOT}/core/include
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
add_dependencies(${PROJECT_APPLICATION_NAME} glfw libglew_static glm TreeVisualizerCore)

