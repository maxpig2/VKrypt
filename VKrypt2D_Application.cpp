//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt2D_Application.h"
#include "VKrypt_2D_render_system.h"

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
        loadGameObjects(VKrypt_2DShapes::SimpleTriangle);
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

    void VKrypt2D_Application::loadGameObjects(VKrypt_2DShapes shape) {
        /*
        std::vector<VKryptMesh::Vertex> vertices{};
        if (shape==VKrypt_2DShapes::SimpleTriangle) {
           vertices= {
           {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
           {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
           {{-0.5f, 0.5f}, {0.0f,0.0f,1.0f}}
            };
        }
        else if (shape==VKrypt_2DShapes::SierpinskiTriangle){
            sierpinski(vertices, 5, {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.0f, -0.5f});
        }
        else if (shape==VKrypt_2DShapes::HexFlower) {
            hexFlower(vertices,2, {0.0f,0.0f},0.5f);
        }
        auto VKrypt_mesh = std::make_shared<VKryptMesh>(VKrypt_device, vertices);

        auto triangle = VKryptGameObject::createGameObject();
        triangle.mesh = VKrypt_mesh;
        triangle.color = {0.f,5.f,.0f};
        triangle.transform2d.translation.x = .01f;


        gameObjects.push_back(std::move(triangle));
        */

        std::vector<VKryptMesh::Vertex> vertices{
               {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
               {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
               {{-0.5f, 0.5f}, {0.0f,0.0f,1.0f}}
        };
        auto VKrypt_mesh = std::make_shared<VKryptMesh>(VKrypt_device,vertices);

        auto triangle = VKryptGameObject::createGameObject();
        triangle.mesh = VKrypt_mesh;
        triangle.color = {.1f,.8f,.1f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {2.f,.5f};
        triangle.transform2d.rotation = .25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }

    void VKrypt2D_Application::sierpinski(
    std::vector<VKryptMesh::Vertex> &vertices,
    int depth,
    glm::vec2 left,
    glm::vec2 right,
    glm::vec2 top) {
        if (depth <= 0) {
            vertices.push_back({top});
            vertices.push_back({right});
            vertices.push_back({left});
        } else {
            auto leftTop = 0.5f * (left + top);
            auto rightTop = 0.5f * (right + top);
            auto leftRight = 0.5f * (left + right);
            sierpinski(vertices, depth - 1, left, leftRight, leftTop);
            sierpinski(vertices, depth - 1, leftRight, right, rightTop);
            sierpinski(vertices, depth - 1, leftTop, rightTop, top);
        }
    }

    void VKrypt2D_Application::hexFlower(
    std::vector<VKryptMesh::Vertex>& vertices,
    int depth,
    glm::vec2 center,
    float radius)
    {
        if (depth <= 0) return;

        for (int i = 0; i < 6; ++i) {
            float angle1 = glm::radians(60.0f * i);
            float angle2 = glm::radians(60.0f * (i + 1));

            glm::vec2 a = center;
            glm::vec2 b = center + glm::vec2(std::cos(angle1), std::sin(angle1)) * radius;
            glm::vec2 c = center + glm::vec2(std::cos(angle2), std::sin(angle2)) * radius;

            vertices.push_back({a});
            vertices.push_back({b});
            vertices.push_back({c});

            glm::vec2 nextCenter = (b + c) * 0.5f;
            hexFlower(vertices, depth - 1, nextCenter, radius * 0.5f);
        }
    }
}