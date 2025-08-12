#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "VKrypt_2D_mesh.h"

namespace VKrypt {
    class ImplicitMeshes2D {

        public:
        //Primitive Meshes
        static void Triangle(std::vector<VKryptMesh2D::Vertex> &vertices);
        static void Circle(std::vector<VKryptMesh2D::Vertex> &vertices, float radius, int segments);
        static void Star(std::vector<VKryptMesh2D::Vertex> &vertices, float outerRadius, float innerRadius, int points);

        // Recursive Meshes
        static void SierpinskiTriangle(std::vector<VKryptMesh2D::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right,glm::vec2 top);
        static void HexFlower(std::vector<VKryptMesh2D::Vertex> &vertices, int depth, glm::vec2 center,float radius);


    };
}
