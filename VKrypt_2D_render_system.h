#pragma once

#include "src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "VKrypt_game_object.h"
#include "src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h"

// std
#include <memory>
#include <vector>

namespace VKrypt {
    class VKrypt2DRenderSystem {
    public:
        VKrypt2DRenderSystem(VKryptDevice &device, VkRenderPass renderPass);
        ~VKrypt2DRenderSystem();

        VKrypt2DRenderSystem(const VKrypt2DRenderSystem &) = delete;
        VKrypt2DRenderSystem &operator=(const VKrypt2DRenderSystem &) = delete;

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<VKryptGameObject> &gameObjects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        VKryptDevice &VKrypt_device;

        std::unique_ptr<VKryptPipeline> VKrypt_pipeline;
        VkPipelineLayout pipelineLayout;
    };
}