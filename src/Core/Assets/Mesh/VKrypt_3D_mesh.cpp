//
// Created by maxtj on 31/07/2025.
//

#include "VKrypt_3D_mesh.h"

#include <ranges>
#include <vector>

#include "../../../Renderer/Vulkan/Device/VKrypt_device.h"

namespace VKrypt {

    VKryptMesh3D::VKryptMesh3D(VKryptDevice &device, const VKryptMesh3D::Builder &builder) : VKrypt_device{device} {
        createVertexBuffers(builder.vertices);
        createIndexBuffers(builder.indices);
    }

    VKryptMesh3D::~VKryptMesh3D() {
        vkDestroyBuffer(VKrypt_device.device(), vertexBuffer, nullptr);
        vkFreeMemory(VKrypt_device.device(), vertexBufferMemory, nullptr);

        if (hasIndexBuffer) {
            vkDestroyBuffer(VKrypt_device.device(), indexBuffer, nullptr);
            vkFreeMemory(VKrypt_device.device(), indexBufferMemory, nullptr);
        }
    }

    void VKryptMesh3D::createVertexBuffers(const std::vector<Vertex3D> &vertices) {
        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3");
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        VKrypt_device.createBuffer(bufferSize,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer,
        stagingBufferMemory);

        void *data;
        vkMapMemory(VKrypt_device.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(VKrypt_device.device(), stagingBufferMemory);

        VKrypt_device.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            vertexBuffer,
            vertexBufferMemory);

        VKrypt_device.copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

        vkDestroyBuffer(VKrypt_device.device(), stagingBuffer, nullptr);
        vkFreeMemory(VKrypt_device.device(), stagingBufferMemory, nullptr);
    }

    void VKryptMesh3D::createIndexBuffers(const std::vector<uint32_t> &indices) {
        indexCount = static_cast<uint32_t>(indices.size());
        hasIndexBuffer = indexCount > 0;

        if (!hasIndexBuffer) {
            return;
        }

        VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        VKrypt_device.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer,
            stagingBufferMemory);

        void *data;
        vkMapMemory(VKrypt_device.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(VKrypt_device.device(), stagingBufferMemory);

        VKrypt_device.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            indexBuffer,
            indexBufferMemory);

        VKrypt_device.copyBuffer(stagingBuffer, indexBuffer, bufferSize);

        vkDestroyBuffer(VKrypt_device.device(), stagingBuffer, nullptr);
        vkFreeMemory(VKrypt_device.device(), stagingBufferMemory, nullptr);
    }

    void VKryptMesh3D::draw(VkCommandBuffer commandBuffer) {
        if (hasIndexBuffer) {
            vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
        } else {
            vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
        }
    }

    void VKryptMesh3D::bind(VkCommandBuffer commandBuffer) {
        VkBuffer vertexBuffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        if (hasIndexBuffer) {
            vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
        }
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
