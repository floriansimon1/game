#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>

namespace game::rendering {
    class UnitSquare {
        public:
            static inline std::vector<GLfloat> vertices {
                // Vertex              Texture
                -0.5f, 0.f, -0.5f,    0.f, 1.f, // Back left
                +0.5f, 0.f, -0.5f,    1.f, 1.f, // Back right
                -0.5f, 0.f, +0.5f,    0.f, 0.f, // Front left
                +0.5f, 0.f, +0.5f,    1.f, 0.f  // Front right
            };

            static inline constexpr GLuint      backLeft   = 0;
            static inline constexpr GLuint      backRight  = 1;
            static inline constexpr GLuint      frontLeft  = 2;
            static inline constexpr GLuint      frontRight = 3;
            static inline const     std::string meshName   = "unit-square";

            static inline std::vector<GLuint> vertexIndices {
                frontLeft, frontRight, backLeft,
                backRight
            };
    };
}
