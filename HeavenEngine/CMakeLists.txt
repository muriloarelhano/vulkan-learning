# CMakeList.txt: projeto de CMake para HeavenEngine, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.10)

# Adicione a origem ao executável deste projeto.
add_executable (HeavenEngine "Core/Heaven.cpp" "Core/Heaven.h" "Core/Window.h" "Core/Window.cpp" "Core/Pipeline.h" "Core/Pipeline.cpp")

if(WIN32)
# Dependencies and Libraries for windows compile
target_include_directories(HeavenEngine PRIVATE Libs/glm 
												  Libs/glfw/include
                                                  $ENV{VULKAN_SDK}/Include)

message($ENV{VULKAN_SDK})

target_link_directories(HeavenEngine PRIVATE Libs/glfw/lib-vc2019
                                               $ENV{VULKAN_SDK}/Lib)

target_link_libraries(HeavenEngine PRIVATE glfw3.lib vulkan-1.lib)

else()
    # For linux OS
    find_package(glfw3 REQUIRED)
    # find_package(GLEW REQUIRED)
    # find_package(OpenGL REQUIRED)
 
    target_include_directories(HeavenEngine PRIVATE Libs/glm)
    target_link_libraries(HeavenEngine glfw)

endif()

# TODO: Adicione testes e instale destinos, se necessário.
