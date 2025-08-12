//
// Created by maxtj on 31/07/2025.
//

#include "VKrypt_3D_mesh.h"

#include <ranges>
#include <vector>

#include "../../../Renderer/Vulkan/Device/VKrypt_device.h"

namespace VKrypt {

    VKryptMesh3D::VKryptMesh3D(
        VKryptDevice& device,
        const std::vector<Vertex3D> &vertices): VKrypt_device{device} {
        createVertexBuffers(vertices);
    }

    VKryptMesh3D::~VKryptMesh3D() {
        vkDestroyBuffer(VKrypt_device.device(), vertexBuffer, nullptr);
        vkFreeMemory(VKrypt_device.device(), vertexBufferMemory, nullptr);
    }

    void VKryptMesh3D::createVertexBuffers(const std::vector<Vertex3D> &vertices) {
        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3");
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
        VKrypt_device.createBuffer(bufferSize,VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            vertexBuffer,
            vertexBufferMemory);

        void *data;
        vkMapMemory(VKrypt_device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(VKrypt_device.device(), vertexBufferMemory);
    }

    void VKryptMesh3D::draw(VkCommandBuffer commandBuffer) {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
    }

    void VKryptMesh3D::bind(VkCommandBuffer commandBuffer) {
        VkBuffer vertexBuffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    }

    std::vector<VkVertexInputBindingDescription> VKryptMesh3D::Vertex3D::getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex3D);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> VKryptMesh3D::Vertex3D::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex3D, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex3D, color);
        return attributeDescriptions;
    }

}
