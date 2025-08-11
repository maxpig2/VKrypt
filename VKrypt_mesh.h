//
// Created by maxtj on 31/07/2025.
//

#pragma once
#include "src/Renderer/Vulkan/Device/VKrypt_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace VKrypt {
    class VKryptMesh {
        public:

        struct Vertex {
            glm::vec2 position;
            glm::vec3 color = glm::vec3(1.0f);
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        VKryptMesh( VKryptDevice &device,const std::vector<Vertex> &vertices);
        ~VKryptMesh();

        VKryptMesh(const VKryptMesh&) = delete;
        VKryptMesh &operator=(const VKryptMesh&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

        private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);
        VKryptDevice &VKrypt_device;
        VkBuffer vertexBuffer{};
        VkDeviceMemory vertexBufferMemory{};
        uint32_t vertexCount{};


    };
}
