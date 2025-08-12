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
        src/Renderer/Vulkan/Window/VKrypt_window.h
        src/Renderer/Vulkan/Window/VKrypt_window.cpp
        Applications/Templates/VKrypt2D_Application.h
        Applications/Templates/VKrypt2D_Application.cpp
        Applications/Templates/VKrypt3D_Application.h
        Applications/Templates/VKrypt3D_Application.cpp
        src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h
        src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.cpp
        src/Renderer/Vulkan/Pipeline/VKrypt_3D_pipeline.h
        src/Renderer/Vulkan/Pipeline/VKrypt_3D_pipeline.cpp
        src/Renderer/Vulkan/Device/VKrypt_device.h
        src/Renderer/Vulkan/Device/VKrypt_device.cpp
        src/Renderer/Vulkan/SwapChain/VKrypt_swap_chain.h
        src/Renderer/Vulkan/SwapChain/VKrypt_swap_chain.cpp
        src/Core/Assets/Mesh/VKrypt_2D_mesh.h
        src/Core/Assets/Mesh/VKrypt_2D_mesh.cpp
        src/Core/Assets/Mesh/VKrypt_3D_mesh.h
        src/Core/Assets/Mesh/VKrypt_3D_mesh.cpp
        src/Core/Assets/GameObject/VKrypt_game_object.h
        src/Core/Assets/GameObject/VKrypt_3D_game_object.h
        VKrypt_renderer.h
        VKrypt_renderer.cpp
        VKrypt_2D_render_system.h
        VKrypt_2D_render_system.cpp
        VKrypt_3D_render_system.h
        VKrypt_3D_render_system.cpp
        Applications/NBodyProblem/NBodyProblem_Application.cpp
        Applications/NBodyProblem/NBodyProblem_Application.h
        src/Core/Assets/Mesh/ImplicitMeshes2D.h
        src/Core/Assets/Mesh/ImplicitMeshes2D.cpp
        VKrypt_camera.h
        VKrypt_camera.cpp
        src/Core/Assets/Input/Keyboard_Controller.h
        src/Core/Assets/Input/Keyboard_Controller.cpp

)

# Link libraries
target_link_libraries(VKrypt ${Vulkan_LIBRARIES} )
target_link_libraries(VKrypt glfw)
target_link_libraries(VKrypt Vulkan::Vulkan glfw)

