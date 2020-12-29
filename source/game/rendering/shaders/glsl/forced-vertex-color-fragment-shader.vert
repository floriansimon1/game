#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 unusedVec3;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 projectionView;
uniform vec4 forcedVertexColor;

void main() {
    vertexColor = forcedVertexColor;
    gl_Position = projectionView * model * vec4(position.x, position.y, position.z, 1.0);
}
