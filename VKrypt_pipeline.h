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
        VkPipelineViewportStateCreateInfo viewport_info;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
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
            const PipelineConfigInfo &configInfo);

        ~VKryptPipeline();

        VKryptPipeline(VKryptPipeline const&) = delete;
        void operator=(const VKryptPipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

        private:
        static std::vector<char> readFile(const std::string& filepath);

        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo);

        void createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule);

        VKryptDevice& VKryptDevice;
        VkPipeline graphicsPipeline{};
        VkShaderModule vertShaderModule{};
        VkShaderModule fragShaderModule{};
    };
}