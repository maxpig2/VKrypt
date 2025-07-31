//
// Created by maxtj on 30/07/2025.
//

#include "VKrypt2D_Application.h"

#include <array>
#include <vector>

namespace VKrypt {

    VKrypt2D_Application::VKrypt2D_Application() {
        loadMeshes(VKrypt_2DShapes::SimpleTriangle);
        createPipelineLayout();
        recreateSwapChain();
        createCommandBuffers();
    }

    VKrypt2D_Application::~VKrypt2D_Application() {
        vkDestroyPipelineLayout(VKrypt_device.device(), pipelineLayout, nullptr);
    }

    void VKrypt2D_Application::run() {
        while (!VKrypt_window.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(VKrypt_device.device());
    }

    void VKrypt2D_Application::loadMeshes(VKrypt_2DShapes shape) {
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
        VKrypt_mesh = std::make_unique<VKryptMesh>(VKrypt_device, vertices);

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
            glm::vec2 b = center + glm::vec2(cos(angle1), sin(angle1)) * radius;
            glm::vec2 c = center + glm::vec2(cos(angle2), sin(angle2)) * radius;

            vertices.push_back({a});
            vertices.push_back({b});
            vertices.push_back({c});

            glm::vec2 nextCenter = (b + c) * 0.5f;
            hexFlower(vertices, depth - 1, nextCenter, radius * 0.5f);
        }
    }


    void VKrypt2D_Application::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if ( vkCreatePipelineLayout(VKrypt_device.device(),&pipelineLayoutInfo,nullptr,&pipelineLayout) != VK_SUCCESS ) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void VKrypt2D_Application::createPipeline() {
        PipelineConfigInfo pipelineConfig {}; //= VKryptPipeline::defaultPipelineConfigInfo(VKrypt_swap_chain->width(),VKrypt_swap_chain->height());
        VKryptPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = VKrypt_swap_chain->getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        VKrypt_pipeline = std::make_unique<VKryptPipeline>(
            VKrypt_device,
            "C:/Users/maxtj/CLionProjects/VKrypt/shaders/simple_shader.vert.spv",
            "C:/Users/maxtj/CLionProjects/VKrypt/shaders/simple_shader.frag.spv",
            pipelineConfig
            );
    }

    void VKrypt2D_Application::recreateSwapChain() {
        auto extent = VKrypt_window.getExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = VKrypt_window.getExtent();
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(VKrypt_device.device());
        //VKrypt_swap_chain = nullptr;
        if (VKrypt_swap_chain == nullptr) {
            VKrypt_swap_chain = nullptr;
            VKrypt_swap_chain = std::make_unique<VKryptSwapChain>(VKrypt_device,extent);
        } else {
            VKrypt_swap_chain = nullptr;
            VKrypt_swap_chain = std::make_unique<VKryptSwapChain>(VKrypt_device,extent, std::move(VKrypt_swap_chain));
            if (VKrypt_swap_chain->imageCount() != commandBuffers.size()) {
                freeCommandBuffers();
                createCommandBuffers();
            }
        }

        createPipeline();
    }


    void VKrypt2D_Application::createCommandBuffers() {
        commandBuffers.resize(VKrypt_swap_chain->imageCount());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = VKrypt_device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(VKrypt_device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers!");
        }
    }

    void VKrypt2D_Application::freeCommandBuffers() {
        vkFreeCommandBuffers(VKrypt_device.device(), VKrypt_device.getCommandPool(), static_cast<float>(commandBuffers.size()), commandBuffers.data());
        commandBuffers.clear();
    }

    void VKrypt2D_Application::recordCommandBuffer(int imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = VKrypt_swap_chain->getRenderPass();
        renderPassInfo.framebuffer = VKrypt_swap_chain->getFrameBuffer(static_cast<uint32_t>(imageIndex));

        renderPassInfo.renderArea.offset = {0,0};
        renderPassInfo.renderArea.extent = VKrypt_swap_chain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(VKrypt_swap_chain->getSwapChainExtent().width);
        viewport.height = static_cast<float>(VKrypt_swap_chain->getSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{{0,0}, VKrypt_swap_chain->getSwapChainExtent()};
        vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
        vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);


        VKrypt_pipeline->bind(commandBuffers[imageIndex]);
        VKrypt_mesh->bind(commandBuffers[imageIndex]);
        VKrypt_mesh->draw(commandBuffers[imageIndex]);

        vkCmdEndRenderPass(commandBuffers[imageIndex]);

        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }



    void VKrypt2D_Application::drawFrame() {
        uint32_t imageIndex = 0;
        auto result = VKrypt_swap_chain->acquireNextImage(&imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire swap chain image!");
        }
        recordCommandBuffer(imageIndex);
        result = VKrypt_swap_chain->submitCommandBuffers(&commandBuffers[imageIndex],&imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || VKrypt_window.wasWindowResized()) {
            VKrypt_window.resetWindowResizedFlag();
            recreateSwapChain();
            return;
        }
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to submit swap chain command buffer!");
        }
    }

}