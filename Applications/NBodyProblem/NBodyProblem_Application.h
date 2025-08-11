//
// Created by maxtj on 30/07/2025.
//
#pragma once

#include "../../VKrypt_window.h"
#include "../../VKrypt_pipeline.h"
#include "../../VKrypt_swap_chain.h"
#include "../../VKrypt_device.h"
#include "../../VKrypt_mesh.h"
#include "../../VKrypt_game_object.h"
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
