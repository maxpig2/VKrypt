#pragma once

#include "src/Renderer/Vulkan/Device/VKrypt_device.h"

// std
#include <memory>
#include <vector>

#include "src/Core/Assets/GameObject/VKrypt_3D_game_object.h"
#include "src/Renderer/Vulkan/Pipeline/VKrypt_3D_pipeline.h"
#include "VKrypt_camera.h"

namespace VKrypt {
    class VKrypt3DRenderSystem {
    public:
        VKrypt3DRenderSystem(VKryptDevice &device, VkRenderPass renderPass);
        ~VKrypt3DRenderSystem();

        VKrypt3DRenderSystem(const VKrypt3DRenderSystem &) = delete;
        VKrypt3DRenderSystem &operator=(const VKrypt3DRenderSystem &) = delete;

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<VKryptGameObject3D> &gameObjects, const VKryptCamera &camera);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        VKryptDevice &VKrypt_device;

        std::unique_ptr<VKryptPipeline3D> VKrypt_pipeline3D;
        VkPipelineLayout pipelineLayout;
    };
}
