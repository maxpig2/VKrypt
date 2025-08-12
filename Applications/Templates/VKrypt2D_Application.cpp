//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt2D_Application.h"
#include "../../VKrypt_2D_render_system.h"
#include "../../src/Core/Assets/Mesh/ImplicitMeshes2D.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <array>
#include <ranges>
#include <vector>

namespace VKrypt {

    VKrypt2D_Application::VKrypt2D_Application() {
        VKrypt2D_Application::loadGameObjects();
    }

    VKrypt2D_Application::~VKrypt2D_Application() {}

    void VKrypt2D_Application::run() {
        VKrypt2DRenderSystem RenderSystem_2D {VKrypt_device, VKrypt_renderer.getSwapChainRenderPass()};
        while (!VKrypt_window.shouldClose()) {
            glfwPollEvents();

            if (auto commandBuffer = VKrypt_renderer.beginFrame()) {
                VKrypt_renderer.beginSwapChainRenderPass(commandBuffer);
                RenderSystem_2D.renderGameObjects(commandBuffer, gameObjects);
                VKrypt_renderer.endSwapChainRenderPass(commandBuffer);
                VKrypt_renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(VKrypt_device.device());
    }

    void VKrypt2D_Application::loadGameObjects() {
        std::vector<VKryptMesh2D::Vertex> vertices;

        ImplicitMeshes2D::Triangle(vertices);

        auto VKrypt_mesh = std::make_shared<VKryptMesh2D>(VKrypt_device,vertices);

        auto triangle = VKryptGameObject::createGameObject();
        triangle.mesh = VKrypt_mesh;
        triangle.color = {.1f,.8f,.1f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {1.f,1.f};
        triangle.transform2d.rotation = .25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }

}