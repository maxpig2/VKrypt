#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <iostream>

#include "Applications/Templates/VKrypt2D_Application.h"
//#include "Applications/NBodyProblem/NBodyProblem_Application.h"

#include <cstdlib>

#include "Applications/Templates/VKrypt3D_Application.h"

int main() {
    VKrypt::VKrypt3D_Application app{};

    try {
        app.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
