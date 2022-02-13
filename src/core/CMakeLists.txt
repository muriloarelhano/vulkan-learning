cmake_minimum_required (VERSION 3.15)

project(core VERSION 1.0.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable (${PROJECT_NAME} ${SOURCE_FILES} )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_sources(${PROJECT_NAME} PUBLIC Vulkan.h Window.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm utilities PRIVATE glfw Vulkan::Vulkan)
