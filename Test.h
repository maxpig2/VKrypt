//
// Created by maxtj on 30/07/2025.
//

#ifndef TEST_H
#define TEST_H

#endif //TEST_H

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

    class Test {
        public:
        static constexpr int Width = 800;
        static constexpr int Height = 600;

        void run();

        Test();
        ~Test();

        Test(const Test&) = delete;
        Test &operator=(const Test&) = delete;

    private:
        void loadMeshes();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        VKryptWindow VKrypt_window{Width,Height,"Test"};
        VKryptDevice VKrypt_device{VKrypt_window};
        VKryptSwapChain VKrypt_swap_chain{VKrypt_device,VKrypt_window.getExtent()};
        std::unique_ptr<VKryptPipeline> VKrypt_pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
       std::unique_ptr<VKryptMesh> VKrypt_mesh;
    };

}
