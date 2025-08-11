#version 450

layout (location = 0) in vec3 vertexColor;

layout (location = 0) out vec4 outColor;
layout (push_constant) uniform Push {
    mat2 transform;
    vec2 positionOffset;
    vec3 color;
} push;

void main() {

    vec3 colorTint = vec3(2.0f,2.0f,2.0f);
    outColor = vec4(vertexColor * colorTint * push.color , 1.0);
}