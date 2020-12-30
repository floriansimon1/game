#pragma once

#include <game/rendering/managed-opengl-resource.hpp>
#include <game/rendering/shader-binding.hpp>

#include <game/base/non-copyable.hpp>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <chrono>

namespace game::rendering {
    class Mesh: private game::base::NonCopyable {
        public:
                                        Mesh(
                                            const std::vector<GLfloat>&     vertices,
                                            const std::vector<GLuint>&      vertexIndices,
                                            std::unique_ptr<sf::Shader>     shader
                                        );

                                        Mesh(
                                            Mesh&&                          mesh
                                        );

            ShaderBinding               bindShader();

            void                        draw(
                                            const glm::mat4&                projectionView,
                                            const glm::mat4&                transform
                                        ) const;

        private:
            std::unique_ptr<sf::Shader> shader;

            ManagedOpenglBuffer         vao;
            ManagedOpenglBuffer         vbo;
            ManagedOpenglBuffer         ebo;
            std::vector<GLfloat>        vertices;
            std::vector<GLuint>         vertexIndices;
    };
}
