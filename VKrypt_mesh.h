//
// Created by maxtj on 31/07/2025.
//

#pragma once
#include "VKrypt_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace VKrypt {
    class VKryptMesh {
        public:

        struct Vertex {
            static std::vector<VkVertexInputBindingDescription> getBindingDescription();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescription();
        };

        VKryptMesh( VKryptDevice &device,const std::vector<Vertex> &vertices);
        ~VKryptMesh();

        VKryptMesh(const VKryptMesh&) = delete;
        VKryptMesh &operator=(const VKryptMesh&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

        private:
        void createVertexBuffer(const std::vector<Vertex> &vertices);
        VKryptDevice &device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;


    };
}
