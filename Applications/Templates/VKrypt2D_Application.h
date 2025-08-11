//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "../../src/Renderer/Vulkan/Window/VKrypt_window.h"
#include "../../src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h"
#include "../../src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "../../src/Core/Assets/Mesh/VKrypt_mesh.h"
#include "../../src/Core/Assets/GameObject/VKrypt_game_object.h"
#include "../../VKrypt_renderer.h"

//std
#include <memory>
#include <vector>

#include "VKrypt_Application.h"

namespace VKrypt {

    class VKrypt2D_Application : public VKrypt_Application {
        public:
        void run() override;

        VKrypt2D_Application();
        ~VKrypt2D_Application() override;

        VKrypt2D_Application(const VKrypt2D_Application&) = delete;
        VKrypt2D_Application &operator=(const VKrypt2D_Application&) = delete;

    private:
        void loadGameObjects() override;
    };

}
