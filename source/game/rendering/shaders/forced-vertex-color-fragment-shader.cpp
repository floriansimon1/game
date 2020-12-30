#include <game/rendering/shaders/forced-vertex-color-fragment-shader.hpp>

#include <game/data/paths.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getForcedVertexColorShader() {
        auto shader = std::make_unique<sf::Shader>();

        shader->loadFromFile(
            game::data::Paths::shadersRoot + "forced-vertex-color-fragment-shader.vert",
            game::data::Paths::shadersRoot + "forced-vertex-color-fragment-shader.frag"
        );

        return shader;
    }

    void
    setForcedVertexColorShader(
        ShaderBinding       binding,
        const sf::Color&    forcedColor
    ) {
        binding.shader.setUniform("forcedVertexColor", sf::Glsl::Vec4(forcedColor));
    }
}
