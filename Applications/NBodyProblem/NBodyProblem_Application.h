//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "../../src/Renderer/Vulkan/Window/VKrypt_window.h"
#include "../../src/Renderer/Vulkan/Pipeline/VKrypt_pipeline.h"
#include "../../src/Renderer/Vulkan/SwapChain/VKrypt_swap_chain.h"
#include "../../src/Renderer/Vulkan/Device/VKrypt_device.h"
#include "../../src/Core/Assets/Mesh/VKrypt_2D_mesh.h"
#include "../../src/Core/Assets/GameObject/VKrypt_game_object.h"
#include "../../VKrypt_renderer.h"

//std
#include <memory>
#include <vector>

namespace VKrypt {

    class NBodyProblem_Application {
    public:
        static constexpr int Width = 800;
        static constexpr int Height = 600;

        void run();

        NBodyProblem_Application();
        ~NBodyProblem_Application();

        NBodyProblem_Application(const NBodyProblem_Application&) = delete;
        NBodyProblem_Application &operator=(const NBodyProblem_Application&) = delete;

    private:
        virtual void loadGameObjects();

        VKryptWindow VKrypt_window{Width,Height,"N Body Problem"};
        VKryptDevice VKrypt_device{VKrypt_window};
        std::vector<VKryptGameObject> gameObjects;
        VKryptRenderer VKrypt_renderer{VKrypt_window,VKrypt_device};
    };

}
