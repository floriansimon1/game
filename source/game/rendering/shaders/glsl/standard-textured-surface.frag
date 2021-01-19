#version 410 core

in vec2 textureCoordinates;

out vec4 fragmentColor;

uniform bool      disableTexture;
uniform vec2      textureScale;
uniform sampler2D textureToMap;

void main() {
    fragmentColor = disableTexture ? vec4(0.f, 0.f, 0.f, 1.f) : texture(textureToMap, textureCoordinates * textureScale);
}
