//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "../../src/Renderer/Vulkan/Window/VKrypt_window.h"
#include "../../src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h"
#include "../../src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "../../VKrypt_mesh.h"
#include "../../VKrypt_game_object.h"
#include "../../VKrypt_renderer.h"

//std
#include <memory>
#include <vector>

namespace VKrypt {

    enum class VKrypt_2DShapes : uint32_t {
        SimpleTriangle = 0,
        SierpinskiTriangle = 1,
        HexFlower = 2
    };

    class VKrypt2D_Application {
        public:
        static constexpr int Width = 800;
        static constexpr int Height = 600;

        void run();

        VKrypt2D_Application();
        ~VKrypt2D_Application();

        VKrypt2D_Application(const VKrypt2D_Application&) = delete;
        VKrypt2D_Application &operator=(const VKrypt2D_Application&) = delete;

    private:
        virtual void loadGameObjects();
        void sierpinski(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right,glm::vec2 top);
        void hexFlower(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 center,float radius);

        VKryptWindow VKrypt_window{Width,Height,"VKrypt 2D"};
        VKryptDevice VKrypt_device{VKrypt_window};
        std::vector<VKryptGameObject> gameObjects;
        VKryptRenderer VKrypt_renderer{VKrypt_window,VKrypt_device};
    };

}
