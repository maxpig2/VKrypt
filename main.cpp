#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <iostream>

#include "VKrypt2D_Application.h"
#include "Applications/NBodyProblem/NBodyProblem_Application.h"

#include <cstdlib>

int main() {
    VKrypt::NBodyProblem_Application app{};

    try {
        app.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}