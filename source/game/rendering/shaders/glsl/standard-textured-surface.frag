#version 410 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform sampler2D textureToMap;

void main() {
    fragmentColor = texture(textureToMap, textureCoordinates);
}
