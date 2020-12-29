#pragma once

#include <glad/glad.h>

#include <vector>

namespace game::rendering {
    static inline std::vector<GLfloat> squareVertices {
        // Vertex               Color
        -0.5f, 0.0f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f, // Back left
        +0.5f, 0.0f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f, // Back right
        -0.5f, 0.0f, +0.5f,    1.0f, 1.0f, 1.0f, 1.0f, // Front left
        +0.5f, 0.0f, +0.5f,    1.0f, 1.0f, 1.0f, 1.0f, // Front right
    };

    static inline constexpr GLuint squareBackLeft   = 0;
    static inline constexpr GLuint squareBackRight  = 1;
    static inline constexpr GLuint squareFrontLeft  = 2;
    static inline constexpr GLuint squareFrontRight = 3;

    static inline std::vector<GLuint> floorTileVertexIndices {
        squareFrontLeft, squareFrontRight, squareBackLeft,
        squareBackRight
    };
}
