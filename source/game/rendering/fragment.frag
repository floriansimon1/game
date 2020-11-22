#version 460 core

in vec2 textureCoordinates;

out vec4 color;

uniform sampler2D textureData;

void main() {
    color = texture(textureData, textureCoordinates);
}
