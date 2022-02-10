cmake_minimum_required (VERSION 3.15)

project(utilities)

add_library(${PROJECT_NAME} VkValidation.h QueueFamily.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Vulkan REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
