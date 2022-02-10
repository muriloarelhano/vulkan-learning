cmake_minimum_required (VERSION 3.15)

project(core)

add_executable (${PROJECT_NAME} Application.h Application.cpp )

target_sources(${PROJECT_NAME} PUBLIC Vulkan.h Window.h PRIVATE Window.cpp Vulkan.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm utilities PRIVATE glfw Vulkan::Vulkan)
