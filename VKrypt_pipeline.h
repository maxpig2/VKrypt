//
// Created by maxtj on 31/07/2025.
//

#ifndef VKRYPT_PIPELINE_H
#define VKRYPT_PIPELINE_H
#include <string>
#include <vector>

#endif //VKRYPT_PIPELINE_H

#pragma once

#define GLFW_INCLUDE_VULKAN
#include "VKrypt_device.h"
#include <string>

namespace VKrypt {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };


    class VKryptPipeline {
        public:
        VKryptPipeline(
            VKryptDevice& device,
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo configInfo);

        ~VKryptPipeline();

        VKryptPipeline(VKryptPipeline const&) = delete;
        void operator=(const VKryptPipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

        private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo);

        void createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule);

        VKryptDevice& VKryptDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}