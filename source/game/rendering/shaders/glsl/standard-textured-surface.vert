#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinatesInput;

out vec4 vertexColor;
out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 projectionView;

void main() {
    gl_Position        = projectionView * model * vec4(position.x, position.y, position.z, 1.0);
    textureCoordinates = textureCoordinatesInput;
}
