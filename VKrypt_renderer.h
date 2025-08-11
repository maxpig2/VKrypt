#pragma once

#include "src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "src/Renderer/Vulkan/SwapChain/VKrypt_swap_chain.h"
#include "src/Renderer/Vulkan/Window/VKrypt_window.h"

// std
#include <cassert>
#include <memory>
#include <vector>

namespace VKrypt {

    class VKryptRenderer {

    public:

        VKryptRenderer(VKryptWindow &window, VKryptDevice &device);
        ~VKryptRenderer();

        VKryptRenderer(const VKryptRenderer &) = delete;
        VKryptRenderer &operator=(const VKryptRenderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const { return VKrypt_swap_chain->getRenderPass(); }
        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        VKryptWindow &VKrypt_window;
        VKryptDevice &VKrypt_device;
        std::unique_ptr<VKryptSwapChain> VKrypt_swap_chain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex = 0;
        bool isFrameStarted =  false;
    };
}  // namespace VKrypt
