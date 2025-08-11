//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt_window.h"

#include <stdexcept>

namespace VKrypt {

    VKryptWindow::VKryptWindow(int width, int height, std::string name) : windowWidth(width), windowHeight(height), windowName(name) {
        initWindow();
    }

    VKryptWindow::~VKryptWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void VKryptWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    void VKryptWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }

    void VKryptWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto VKrypt_window = reinterpret_cast<VKryptWindow *>(glfwGetWindowUserPointer(window));
        VKrypt_window->windowWidth = width;
        VKrypt_window->windowHeight = height;

    }

}
