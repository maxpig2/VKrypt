cmake_minimum_required(VERSION 3.31)
project(VKrypt)

set(CMAKE_CXX_STANDARD 20)

#[[set(CMAKE_PREFIX_PATH "C:/vcpkg/packages/glfw3_x64-windows")
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE glfw)]]

# Vulkan
find_package(Vulkan REQUIRED)
#[[if (Vulkan_FOUND)
    include_directories(${VULKAN_INCLUDE_DIRS})
    link_directories(${VULKAN_LIBRARY_DIRS})
endif ()]]

# GLFW (required for windowing)
find_package(glfw3 3.4 REQUIRED)

add_executable(VKrypt main.cpp
        VKrypt_window.h
        VKrypt_window.cpp
        VKrypt2D_Application.h
        VKrypt2D_Application.cpp
        VKrypt_pipeline.h
        VKrypt_pipeline.cpp
        VKrypt_device.h
        VKrypt_device.cpp
        VKrypt_swap_chain.h
        VKrypt_swap_chain.cpp
        VKrypt_mesh.h
        VKrypt_mesh.cpp
        VKrypt_game_object.h
        VKrypt_renderer.h
        VKrypt_renderer.cpp
        VKrypt_2D_render_system.h
        VKrypt_2D_render_system.cpp
        Applications/NBodyProblem/NBodyProblem_Application.cpp
        Applications/NBodyProblem/NBodyProblem_Application.h
)

# Link libraries
target_link_libraries(VKrypt ${Vulkan_LIBRARIES} )
target_link_libraries(VKrypt glfw)
target_link_libraries(VKrypt Vulkan::Vulkan glfw)

