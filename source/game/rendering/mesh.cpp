#include <game/rendering/mesh.hpp>

constexpr GLuint       positionAttribute        = 0;
constexpr GLuint       textureAttribute         = 1;

constexpr unsigned int textureNumbersPerVertex  = 2;
constexpr unsigned int positionNumbersPerVertex = 3;

constexpr unsigned int numbersPerVertex         = positionNumbersPerVertex + textureNumbersPerVertex;

namespace game::rendering {
    Mesh::Mesh(
        const std::vector<GLfloat>& vertices,
        const std::vector<GLuint>&  vertexIndices,
        std::unique_ptr<sf::Shader> shader
    )
    : shader(std::move(shader))
    , vao(ManagedOpenglBuffer::createGenericBuffer())
    , vbo(ManagedOpenglBuffer::createVertexArray())
    , ebo(ManagedOpenglBuffer::createGenericBuffer())
    , vertices(vertices)
    , vertexIndices(vertexIndices) {
        glBindVertexArray(this->vao.unwrap());

        glBindBuffer(GL_ARRAY_BUFFER,         this->vbo.unwrap());

        glBufferData(GL_ARRAY_BUFFER,         this->vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo.unwrap());

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndices.size() * sizeof(GLuint), this->vertexIndices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(positionAttribute, positionNumbersPerVertex, GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(GLfloat), reinterpret_cast<void*>(0));
        glVertexAttribPointer(textureAttribute,  textureNumbersPerVertex,  GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(GLfloat), reinterpret_cast<void*>(positionNumbersPerVertex * sizeof(GLfloat)));

        glEnableVertexAttribArray(textureAttribute);
        glEnableVertexAttribArray(positionAttribute);
    }

    Mesh::Mesh(
        Mesh&& mesh
    )
    : shader(std::move(mesh.shader))
    , vao(std::move(mesh.vao))
    , vbo(std::move(mesh.vbo))
    , ebo(std::move(mesh.ebo))
    , vertices(std::move(mesh.vertices))
    , vertexIndices(std::move(mesh.vertexIndices))
    {}

    ShaderBinding
    Mesh::bindShader() {
        return { *this->shader };
    }

    void
    Mesh::draw(
        const glm::mat4& projectionView,
        const glm::mat4& transform
    ) const {
        sf::Shader::bind(this->shader.get());

        this->shader->setUniform("model",          sf::Glsl::Mat4(glm::value_ptr(transform)));
        this->shader->setUniform("projectionView", sf::Glsl::Mat4(glm::value_ptr(projectionView)));

        glBindVertexArray(this->vao.unwrap());

        glDrawElements(GL_TRIANGLE_STRIP, this->vertexIndices.size(), GL_UNSIGNED_INT, 0);

        sf::Shader::bind(nullptr);
    }
}
