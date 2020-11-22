#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 inputTextureCoordinates;

out vec2 textureCoordinates;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main() {
    textureCoordinates  = inputTextureCoordinates;
    gl_Position         = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
}
