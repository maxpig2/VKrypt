//
// Created by maxtj on 31/07/2025.
//

#pragma once
#include "../../../Renderer/Vulkan/Device/VKrypt_device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <memory>
#include <glm/glm.hpp>

namespace VKrypt {
    class VKryptMesh3D {
        public:

        struct Vertex3D {
            glm::vec3 position {};
            glm::vec3 color = glm::vec3(1.0f);
            glm::vec3 normal{};
            glm::vec2 uv{};
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            bool operator==(const Vertex3D &other) const {
                return position == other.position && color == other.color && normal == other.normal &&
                       uv == other.uv;
            }
        };

        struct Builder {
            std::vector<Vertex3D> vertices{};
            std::vector<uint32_t> indices{};
            void loadModel(const std::string &filepath);
        };

        VKryptMesh3D(VKryptDevice &device, const VKryptMesh3D::Builder &builder);
        ~VKryptMesh3D();

        VKryptMesh3D(const VKryptMesh3D&) = delete;
        VKryptMesh3D &operator=(const VKryptMesh3D&) = delete;

        static std::unique_ptr<VKryptMesh3D> createModelFromFile(
            VKryptDevice &device, const std::string &filepath);

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

        private:
        void createVertexBuffers(const std::vector<Vertex3D> &vertices);
        void createIndexBuffers(const std::vector<uint32_t> &indices);
        VKryptDevice &VKrypt_device;
        VkBuffer vertexBuffer{};
        VkDeviceMemory vertexBufferMemory{};
        uint32_t vertexCount{};

        bool hasIndexBuffer = false;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        uint32_t indexCount;

    };
}
