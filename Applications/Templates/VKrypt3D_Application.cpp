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
#include <filesystem>
#include <iostream>
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

    void VKrypt3D_Application::loadGameObjects() {
        std::shared_ptr<VKryptMesh3D> VKrypt_mesh =
            VKryptMesh3D::createModelFromFile(VKrypt_device, "C:/Users/maxtj/CLionProjects/VKrypt/src/Core/Assets/Mesh/Obj/teapot.obj");
        auto gameObj = VKryptGameObject3D::createGameObject();
        gameObj.mesh = VKrypt_mesh;
        gameObj.transform.translation = {.0f, .0f, 2.5f};
        gameObj.transform.scale = glm::vec3(-1.f);
        gameObjects.push_back(std::move(gameObj));
    }

}
