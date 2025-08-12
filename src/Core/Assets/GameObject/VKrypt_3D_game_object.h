//
// Created by maxtj on 1/08/2025.
//

#pragma once

#include "../Mesh/VKrypt_2D_mesh.h"

#include <memory>
#include <glm/gtc/matrix_transform.hpp>


namespace VKrypt {
    class VKryptMesh3D;

    struct TransformComponent {
        glm::vec3 translation{};
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        // Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
        glm::mat4 mat4() {
            const float c3 = glm::cos(rotation.z);
            const float s3 = glm::sin(rotation.z);
            const float c2 = glm::cos(rotation.x);
            const float s2 = glm::sin(rotation.x);
            const float c1 = glm::cos(rotation.y);
            const float s1 = glm::sin(rotation.y);
            return glm::mat4{
                {
                    scale.x * (c1 * c3 + s1 * s2 * s3),
                    scale.x * (c2 * s3),
                    scale.x * (c1 * s2 * s3 - c3 * s1),
                    0.0f,
                },
                {
                    scale.y * (c3 * s1 * s2 - c1 * s3),
                    scale.y * (c2 * c3),
                    scale.y * (c1 * c3 * s2 + s1 * s3),
                    0.0f,
                },
                {
                    scale.z * (c2 * s1),
                    scale.z * (-s2),
                    scale.z * (c1 * c2),
                    0.0f,
                },
                {translation.x, translation.y, translation.z, 1.0f}};
        }
    };

    class VKryptGameObject3D {
    public:
        using id_t = unsigned int;

        static VKryptGameObject3D createGameObject() {
            static id_t currentId = 0;
            return VKryptGameObject3D(currentId++);
        }

        VKryptGameObject3D(const VKryptGameObject3D&) = delete;
        VKryptGameObject3D& operator=(const VKryptGameObject3D&) = delete;
        VKryptGameObject3D(VKryptGameObject3D&&) = default;
        VKryptGameObject3D &operator=(VKryptGameObject3D&&) = default;

        id_t getId() {return id;}

        std::shared_ptr<VKrypt::VKryptMesh3D> mesh{};
        glm::vec3 color{};
        TransformComponent transform{};

    private:
        VKryptGameObject3D(id_t objId) : id{objId} {}
        id_t id;
    };
};
