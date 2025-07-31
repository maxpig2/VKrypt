//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "VKrypt_window.h"
#include "VKrypt_pipeline.h"
#include "VKrypt_swap_chain.h"
#include "VKrypt_device.h"
#include "VKrypt_mesh.h"

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
        void loadMeshes(VKrypt_2DShapes shape);
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        void sierpinski(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right,glm::vec2 top);
        void hexFlower(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 center,float radius);

        VKryptWindow VKrypt_window{Width,Height,"Test"};
        VKryptDevice VKrypt_device{VKrypt_window};
        VKryptSwapChain VKrypt_swap_chain{VKrypt_device,VKrypt_window.getExtent()};
        std::unique_ptr<VKryptPipeline> VKrypt_pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
       std::unique_ptr<VKryptMesh> VKrypt_mesh;
    };

}
