#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "VKrypt_mesh.h"

namespace VKrypt {
    class ImplicitMeshes2D {

        public:
        //Primitive Meshes
        static void Triangle(std::vector<VKryptMesh::Vertex> &vertices);
        static void Circle(std::vector<VKryptMesh::Vertex> &vertices, float radius, int segments);
        static void Star(std::vector<VKryptMesh::Vertex> &vertices, float outerRadius, float innerRadius, int points);

        // Recursive Meshes
        static void SierpinskiTriangle(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right,glm::vec2 top);
        static void HexFlower(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 center,float radius);


    };
}
