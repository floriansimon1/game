#version 410 core

in vec2  textureCoordinates;
in float distanceToOrigin;

out vec4 fragmentColor;

uniform bool      disableTexture;
uniform vec2      textureScale;
uniform sampler2D textureToMap;

void main() {
    float lightFactor = .9f;

    if (distanceToOrigin > 38.f) {
        lightFactor = 0.7f;
    } else if (distanceToOrigin > 30.f) {
        lightFactor = 0.8f;
    } else if (distanceToOrigin > 5.f) {
        lightFactor = 0.85f;
    }

    fragmentColor = disableTexture ? vec4(0.f, 0.f, 0.f, 1.f) : lightFactor * texture(textureToMap, textureCoordinates * textureScale);
}
