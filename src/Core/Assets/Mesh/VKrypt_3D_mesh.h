//
// Created by maxtj on 31/07/2025.
//

#pragma once
#include "../../../Renderer/Vulkan/Device/VKrypt_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace VKrypt {
    class VKryptMesh3D {
        public:

        struct Vertex3D {
            glm::vec3 position {};
            glm::vec3 color = glm::vec3(1.0f);
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        VKryptMesh3D( VKryptDevice &device,const std::vector<Vertex3D> &vertices);
        ~VKryptMesh3D();

        VKryptMesh3D(const VKryptMesh3D&) = delete;
        VKryptMesh3D &operator=(const VKryptMesh3D&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

        private:
        void createVertexBuffers(const std::vector<Vertex3D> &vertices);
        VKryptDevice &VKrypt_device;
        VkBuffer vertexBuffer{};
        VkDeviceMemory vertexBufferMemory{};
        uint32_t vertexCount{};


    };
}
