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
    setTextureForStandardTexturedShader(
        ShaderBinding       binding,
        const sf::Texture&  texture
    ) {
        binding.shader.setUniform("textureToMap", texture);
    }
}
