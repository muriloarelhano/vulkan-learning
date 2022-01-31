# CMakeList.txt: projeto de CMake para HeavenEngine, incluir origem e definir
# lógica específica a um projeto aqui.
cmake_minimum_required (VERSION 3.13)

project(HeavenEngine)

# library find
message($ENV{VULKAN_SDK})

find_package(Vulkan REQUIRED)

file(GLOB SOURCES "src/**/*.cpp" )

# add external libraries
add_subdirectory(external/glm)
add_subdirectory(external/glfw)

# Adicione a origem ao executável deste projeto.
add_executable (${PROJECT_NAME} src/core/Application.cpp src/core/Application.h 
                             src/core/Window.h src/core/Window.cpp
                             src/core/Vulkan.h src/core/Vulkan.cpp)

add_subdirectory(src/utilities)


target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		external/glm 
	PRIVATE
		external/glfw/include
		$ENV{VULKAN_SDK}/Include
		utilities
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		glm
	PRIVATE
		glfw3.lib
		vulkan-1.lib 
		utilities
)

