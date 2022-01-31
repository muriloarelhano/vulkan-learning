project(utilities)

# Adicione a origem ao executável deste projeto.
add_library(${PROJECT_NAME} QueueFamily.cpp QueueFamily.h VkValidation.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VULKAN_SDK}/Include)

target_link_directories(${PROJECT_NAME} PRIVATE $ENV{VULKAN_SDK}/Lib)

target_link_libraries(${PROJECT_NAME} PRIVATE vulkan-1.lib)