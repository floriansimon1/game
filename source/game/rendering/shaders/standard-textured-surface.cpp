#include <game/rendering/shaders/standard-textured-surface.hpp>

#include <game/data/paths.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getStandardTexturedSurfaceShader() {
        auto shader = std::make_unique<sf::Shader>();

        shader->loadFromFile(
            game::data::Paths::shadersRoot + "standard-textured-surface.vert",
            game::data::Paths::shadersRoot + "standard-textured-surface.frag"
        );

        return shader;
    }

    void
    unsetTextureForStandardTexturedShader(
        ShaderBinding       binding
    ) {
        binding.shader.setUniform("disableTexture", true);
    }

    void
    setTextureForStandardTexturedShader(
        ShaderBinding       binding,
        const sf::Texture&  texture,
        const float         textureXScale,
        const float         textureYScale
    ) {
        binding.shader.setUniform("disableTexture", false);
        binding.shader.setUniform("textureToMap",   texture);
        binding.shader.setUniform("textureScale",   sf::Vector2f(textureXScale, textureYScale));
    }
}
