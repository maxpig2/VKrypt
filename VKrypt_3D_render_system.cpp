// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include "VKrypt_3D_render_system.h"

#include <array>
#include <cassert>
#include <stdexcept>

#include "src/Core/Assets/Mesh/VKrypt_3D_mesh.h"
#include "src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "src/Renderer/Vulkan/Pipeline/VKrypt_3D_pipeline.h"

namespace VKrypt {

struct SimplePushConstantData {
  glm::mat4 transform{1.f};
  alignas(16) glm::vec3 color{};
};

VKrypt3DRenderSystem::VKrypt3DRenderSystem(VKryptDevice& device, VkRenderPass renderPass)
    : VKrypt_device{device} {
  createPipelineLayout();
  createPipeline(renderPass);
}

VKrypt3DRenderSystem::~VKrypt3DRenderSystem() {
  vkDestroyPipelineLayout(VKrypt_device.device(), pipelineLayout, nullptr);
}

void VKrypt3DRenderSystem::createPipelineLayout() {
  VkPushConstantRange pushConstantRange{};
  pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
  pushConstantRange.offset = 0;
  pushConstantRange.size = sizeof(SimplePushConstantData);

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 1;
  pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
  if (vkCreatePipelineLayout(VKrypt_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }
}

void VKrypt3DRenderSystem::createPipeline(VkRenderPass renderPass) {
  assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

  PipelineConfigInfo3D pipelineConfig{};
  VKryptPipeline3D::defaultPipelineConfigInfo(pipelineConfig);
  pipelineConfig.renderPass = renderPass;
  pipelineConfig.pipelineLayout = pipelineLayout;
  VKrypt_pipeline3D = std::make_unique<VKryptPipeline3D>(
      VKrypt_device,
      "C:/Users/maxtj/CLionProjects/VKrypt/shaders/simple_3D_shader.vert.spv",
      "C:/Users/maxtj/CLionProjects/VKrypt/shaders/simple_3D_shader.frag.spv",
      pipelineConfig);
}

void VKrypt3DRenderSystem::renderGameObjects(
    VkCommandBuffer commandBuffer, std::vector<VKryptGameObject3D>& gameObjects,const VKryptCamera &camera) {
  VKrypt_pipeline3D->bind(commandBuffer);

  auto projectionView = camera.getProjection() * camera.getView();

  for (auto& obj : gameObjects) {
    /*obj.transform.rotation.y = glm::mod(obj.transform.rotation.y + 0.001f, glm::two_pi<float>());
    obj.transform.rotation.x = glm::mod(obj.transform.rotation.x + 0.0005f, glm::two_pi<float>());*/

    SimplePushConstantData push{};
    push.color = obj.color;
    push.transform = projectionView * obj.transform.mat4();

    vkCmdPushConstants(
        commandBuffer,
        pipelineLayout,
        VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
        0,
        sizeof(SimplePushConstantData),
        &push);
    obj.mesh->bind(commandBuffer);
    obj.mesh->draw(commandBuffer);
  }
}

}