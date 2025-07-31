//
// Created by maxtj on 30/07/2025.
//

#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

/*#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>*/


#include <string>

namespace VKrypt {

    class VKryptWindow {
        public:
            VKryptWindow(int width, int height, std::string name);
            ~VKryptWindow();

            VKryptWindow(const VKryptWindow&) = delete;
            VKryptWindow &operator=(const VKryptWindow&) = delete;

            bool shouldClose() {return glfwWindowShouldClose(window);}

            VkExtent2D getExtent() {return {static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight)};}

            void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
        private:
            void initWindow();
            const int windowWidth;
            const int windowHeight;
            std::string windowName;
            GLFWwindow* window;
    };

}