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
            bool wasWindowResized(){return framebufferResized;}
            void resetWindowResizedFlag(){framebufferResized = false;}

            void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
        private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
            void initWindow();
            int windowWidth;
            int windowHeight;
            bool framebufferResized = false;
            std::string windowName;
            GLFWwindow* window;
    };

}