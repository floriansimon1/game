#include <game/rendering/shaders/forced-vertex-color-fragment-shader.hpp>

#include <game/data/paths.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getForcedVertexColorShader(
        const sf::Color forcedColor
    ) {
        auto shader = std::make_unique<sf::Shader>();

        shader->loadFromFile(
            game::data::Paths::shadersRoot + "forced-vertex-color-fragment-shader.vert",
            game::data::Paths::shadersRoot + "forced-vertex-color-fragment-shader.frag"
        );

        sf::Shader::bind(shader.get());

        shader->setUniform("forcedVertexColor", sf::Glsl::Vec4(forcedColor));

        sf::Shader::bind(nullptr);

        return shader;
    }
}
