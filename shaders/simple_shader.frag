#version 450

layout (location = 0) in vec3 vertexColor;

layout (location = 0) out vec4 outColor;


void main() {

    vec3 colorTint = vec3(2.0f,2.0f,2.0f);
    outColor = vec4(vertexColor * colorTint, 1.0);
}