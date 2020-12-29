#pragma once

#include <game/levels/level.hpp>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>
#include <chrono>

namespace game::rendering {
    class RenderObject {
        public:
                                        RenderObject(
                                            const std::vector<GLfloat>&     vertexData,
                                            const std::vector<GLuint>&      vertexIndexData,
                                            const glm::mat4                 model,
                                            std::unique_ptr<sf::Shader>     shader
                                        );

            void                        animate(
                                            const std::chrono::milliseconds Δt 
                                        );

            void                        draw(
                                            const glm::mat4&                projectionView
                                        );

            glm::mat4                   model;

        private:
            std::unique_ptr<sf::Shader> shader;

            GLuint                      vao;
            GLuint                      vbo;
            GLuint                      ebo;
            std::vector<GLfloat>        vertexData;
            std::vector<GLuint>         vertexIndexData;
    };
}
