cmake_minimum_required (VERSION 3.15)

project(utilities)

# Setup library 
add_library(${PROJECT_NAME} STATIC "VkValidation.h" "QueueFamily.h" "VkValidation.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Configuration parameters
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Include dependencies
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
