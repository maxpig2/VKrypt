#include "ImplicitMeshes2D.h"

#include <glm/gtc/constants.hpp>

namespace VKrypt {

    void ImplicitMeshes2D::Triangle(std::vector<VKryptMesh::Vertex> &vertices) {
        // Define an upright triangle centered at the origin
        glm::vec2 top(0.0f, -0.5f);
        glm::vec2 left(0.5f, 0.5f);
        glm::vec2 right(-0.5f, 0.5f);

        // Push vertices in counter-clockwise winding
        vertices.push_back({ top,  glm::vec3(1.0f, 0.0f, 0.0f) });
        vertices.push_back({ right, glm::vec3(0.0f, 1.0f, 0.0f) });
        vertices.push_back({ left,  glm::vec3(0.0f, 0.0f, 1.0f) });
    }

    void ImplicitMeshes2D::SierpinskiTriangle(std::vector<VKryptMesh::Vertex> &vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top) {
        if (depth <= 0) {
            vertices.push_back({top});
            vertices.push_back({right});
            vertices.push_back({left});
        } else {
            auto leftTop = 0.5f * (left + top);
            auto rightTop = 0.5f * (right + top);
            auto leftRight = 0.5f * (left + right);
            SierpinskiTriangle(vertices, depth - 1, left, leftRight, leftTop);
            SierpinskiTriangle(vertices, depth - 1, leftRight, right, rightTop);
            SierpinskiTriangle(vertices, depth - 1, leftTop, rightTop, top);
        }
    }

    void ImplicitMeshes2D::HexFlower(std::vector<VKryptMesh::Vertex> &vertices, const int depth, const glm::vec2 center, const float radius) {
        if (depth <= 0) {
            return;
        }

        for (int i = 0; i < 6; ++i) {
            float angle1 = glm::radians(60.0f * i);
            float angle2 = glm::radians(60.0f * (i + 1));

            glm::vec2 a = center;
            glm::vec2 b = center + glm::vec2(std::cos(angle1), std::sin(angle1)) * radius;
            glm::vec2 c = center + glm::vec2(std::cos(angle2), std::sin(angle2)) * radius;

            vertices.push_back({a});
            vertices.push_back({b});
            vertices.push_back({c});

            glm::vec2 nextCenter = (b + c) * 0.5f;
            HexFlower(vertices, depth - 1, nextCenter, radius * 0.5f);
        }
    }

    void ImplicitMeshes2D::Circle(std::vector<VKryptMesh::Vertex> &vertices, float radius, int segments) {
        vertices.clear();

        glm::vec3 color(1.0f); // white
        glm::vec2 center(0.0f);

        float step = glm::two_pi<float>() / segments;
        for (int i = 0; i < segments; ++i) {
            float a0 = i * step;
            float a1 = (i + 1) * step;

            glm::vec2 p0 = center;
            glm::vec2 p1 = center + glm::vec2(std::cos(a0), std::sin(a0)) * radius;
            glm::vec2 p2 = center + glm::vec2(std::cos(a1), std::sin(a1)) * radius;

            vertices.push_back({ p0, color });
            vertices.push_back({ p1, color });
            vertices.push_back({ p2, color });
        }
    }

    void ImplicitMeshes2D::Star(std::vector<VKryptMesh::Vertex> &vertices, float outerRadius, float innerRadius, int points) {
        vertices.clear();

        glm::vec3 color(1.0f);
        float step = glm::pi<float>() / points; // half-step for inner points

        std::vector<glm::vec2> outline;
        for (int i = 0; i < points * 2; ++i) {
            float r = (i % 2 == 0) ? outerRadius : innerRadius;
            float angle = i * step - glm::half_pi<float>();
            outline.push_back({ std::cos(angle) * r, std::sin(angle) * r });
        }

        // Triangulate as a fan from center
        glm::vec2 center(0.0f);
        for (size_t i = 0; i < outline.size(); ++i) {
            size_t next = (i + 1) % outline.size();
            vertices.push_back({ center, color });
            vertices.push_back({ outline[i], color });
            vertices.push_back({ outline[next], color });
        }
    }

}
