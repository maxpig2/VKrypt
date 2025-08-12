//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt3D_Application.h"
#include "../../VKrypt_3D_render_system.h"
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

#include "../../VKrypt_3D_render_system.h"
#include "../../src/Core/Assets/GameObject/VKrypt_3D_game_object.h"
#include "../../src/Core/Assets/Mesh/VKrypt_3D_mesh.h"

namespace VKrypt {

    VKrypt3D_Application::VKrypt3D_Application() {
        VKrypt3D_Application::loadGameObjects();
    }

    VKrypt3D_Application::~VKrypt3D_Application() {}

    void VKrypt3D_Application::run() {
        VKrypt3DRenderSystem RenderSystem_3D {VKrypt_device, VKrypt_renderer.getSwapChainRenderPass()};
        while (!VKrypt_window.shouldClose()) {
            glfwPollEvents();

            if (auto commandBuffer = VKrypt_renderer.beginFrame()) {
                VKrypt_renderer.beginSwapChainRenderPass(commandBuffer);
                RenderSystem_3D.renderGameObjects(commandBuffer, gameObjects);
                VKrypt_renderer.endSwapChainRenderPass(commandBuffer);
                VKrypt_renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(VKrypt_device.device());
    }

    std::unique_ptr<VKryptMesh3D> createCubeModel(VKryptDevice& device, glm::vec3 offset) {
        std::vector<VKryptMesh3D::Vertex3D> vertices{
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},

        };
        for (auto& v : vertices) {
            v.position += offset;
        }
        return std::make_unique<VKryptMesh3D>(device, vertices);
    }

    void VKrypt3D_Application::loadGameObjects() {
        std::shared_ptr<VKryptMesh3D> VKrypt_mesh = createCubeModel(VKrypt_device, {.0f, .0f, .0f});
        auto cube = VKryptGameObject3D::createGameObject();
        cube.mesh = VKrypt_mesh;
        cube.transform.translation = {.0f, .0f, .5f};
        cube.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(cube));
    }

}
