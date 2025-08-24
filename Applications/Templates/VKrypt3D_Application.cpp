//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt3D_Application.h"
#include "../../VKrypt_3D_render_system.h"
#include "../../src/Core/Assets/Mesh/ImplicitMeshes2D.h"
#include "../../VKrypt_camera.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <algorithm>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <array>
#include <chrono>
#include <ranges>
#include <vector>

#include "../../VKrypt_3D_render_system.h"
#include "../../src/Core/Assets/GameObject/VKrypt_3D_game_object.h"
#include "../../src/Core/Assets/Input/Keyboard_Controller.h"
#include "../../src/Core/Assets/Mesh/VKrypt_3D_mesh.h"

namespace VKrypt {

    VKrypt3D_Application::VKrypt3D_Application() {
        VKrypt3D_Application::loadGameObjects();
    }

    VKrypt3D_Application::~VKrypt3D_Application() {}

    void VKrypt3D_Application::run() {
        VKrypt3DRenderSystem RenderSystem_3D {VKrypt_device, VKrypt_renderer.getSwapChainRenderPass()};
        VKryptCamera camera{};
        //camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
        camera.setViewTarget(glm::vec3(-1.f,-2.f,2.f), glm::vec3(0.f, 0.f, 3.5f));

        auto viewerObject = VKryptGameObject3D::createGameObject();
        Keyboard_Controller cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!VKrypt_window.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            auto deltaTime = std::chrono::duration<float,std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(VKrypt_window.getGLFWWindow(), deltaTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = VKrypt_renderer.getAspectRatio();
            camera.setOrthographicProjection(-aspect,aspect,-1,1,-1,1);
            camera.setPerspectiveProjection(glm::radians(45.0f),aspect,0.1f,100.0f);

            if (auto commandBuffer = VKrypt_renderer.beginFrame()) {
                VKrypt_renderer.beginSwapChainRenderPass(commandBuffer);
                RenderSystem_3D.renderGameObjects(commandBuffer, gameObjects,camera);
                VKrypt_renderer.endSwapChainRenderPass(commandBuffer);
                VKrypt_renderer.endFrame();
            }
        }
        vkDeviceWaitIdle(VKrypt_device.device());
    }

    std::unique_ptr<VKryptMesh3D> createCubeModel(VKryptDevice& device, glm::vec3 offset) {
        VKryptMesh3D::Builder modelBuilder{};
        modelBuilder.vertices = {
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},

        };
        for (auto& v : modelBuilder.vertices) {
            v.position += offset;
        }
        modelBuilder.indices = {0,  1,  2,  0,  3,  1,  4,  5,  6,  4,  7,  5,  8,  9,  10, 8,  11, 9,
                        12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21};

        return std::make_unique<VKryptMesh3D>(device, modelBuilder);
    }

    void VKrypt3D_Application::loadGameObjects() {
        std::shared_ptr<VKryptMesh3D> VKrypt_mesh = createCubeModel(VKrypt_device, {.0f, .0f, .0f});
        auto cube = VKryptGameObject3D::createGameObject();
        cube.mesh = VKrypt_mesh;
        cube.transform.translation = {.0f, .0f, 3.5f};
        cube.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(cube));
    }

}
