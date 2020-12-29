#include <game/rendering/render-object.hpp>

constexpr GLuint       positionAttribute     = 0;
constexpr GLuint       colorAttribute        = 1;
constexpr unsigned int numbersPerVertex      = 3 + 4;

namespace game::rendering {
    RenderObject::RenderObject(
        const std::vector<GLfloat>& vertexData,
        const std::vector<GLuint>&  vertexIndexData,
        const glm::mat4             model,
        std::unique_ptr<sf::Shader> shader
    )
    : model(model)
    , shader(std::move(shader))
    , vertexData(vertexData)
    , vertexIndexData(vertexIndexData) {
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        glGenVertexArrays(1, &this->vao);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER,         this->vbo);

        glBufferData(GL_ARRAY_BUFFER,         this->vertexData.size() * sizeof(GLfloat), this->vertexData.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndexData.size() * sizeof(GLuint), this->vertexIndexData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glVertexAttribPointer(colorAttribute,    4, GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

        glEnableVertexAttribArray(colorAttribute);
        glEnableVertexAttribArray(positionAttribute);
    }

    void
    RenderObject::animate(
        const std::chrono::milliseconds
    ) {}

    void
    RenderObject::draw(
        const glm::mat4& projectionView
    ) {
        sf::Shader::bind(this->shader.get());

        shader->setUniform("model",          sf::Glsl::Mat4(glm::value_ptr(this->model)));
        shader->setUniform("projectionView", sf::Glsl::Mat4(glm::value_ptr(projectionView)));

        glBindVertexArray(this->vao);

        glDrawElements(GL_TRIANGLE_STRIP, this->vertexIndexData.size(), GL_UNSIGNED_INT, 0);

        sf::Shader::bind(nullptr);
    }
}