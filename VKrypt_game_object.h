//
// Created by maxtj on 1/08/2025.
//

#pragma once

#include "VKrypt_mesh.h"

#include <memory>

namespace VKrypt {

    struct Transform2dComponent {
        glm::vec2 translation{};
        glm::vec2 scale{1.f,1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotationMatrix{{c,s}, {-s,c}};
            glm::mat2 scaleMatrix{{scale.x,.0f},{.0f,scale.y}};
            return rotationMatrix * scaleMatrix;
        }
    };

    class VKryptGameObject {
    public:
        using id_t = unsigned int;

        static VKryptGameObject createGameObject() {
            static id_t currentId = 0;
            return VKryptGameObject(currentId++);
        }

        VKryptGameObject(const VKryptGameObject&) = delete;
        VKryptGameObject& operator=(const VKryptGameObject&) = delete;
        VKryptGameObject(VKryptGameObject&&) = default;
        VKryptGameObject &operator=(VKryptGameObject&&) = default;

        id_t getId() {return id;}

        std::shared_ptr<VKrypt::VKryptMesh> mesh{};
        glm::vec3 color{};
        Transform2dComponent transform2d{};

    private:
        VKryptGameObject(id_t objId) : id{objId} {}
        id_t id;
    };
}
