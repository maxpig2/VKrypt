//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "../../src/Renderer/Vulkan/Window/VKrypt_window.h"
#include "../../src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h"
#include "../../src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "../../src/Core/Assets/Mesh/VKrypt_2D_mesh.h"
#include "../../src/Core/Assets/GameObject/VKrypt_game_object.h"
#include "../../VKrypt_renderer.h"

//std
#include <memory>
#include <vector>

namespace VKrypt {

    class VKrypt_Application {
        public:
        virtual ~VKrypt_Application() = default;

        static constexpr int Width = 800;
        static constexpr int Height = 600;

        virtual void run() = 0;

    protected:
        virtual void loadGameObjects() = 0;

        VKryptWindow VKrypt_window{Width,Height,"Application"};
        VKryptDevice VKrypt_device{VKrypt_window};

        VKryptRenderer VKrypt_renderer{VKrypt_window,VKrypt_device};
    };

}
