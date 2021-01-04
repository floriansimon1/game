#pragma once

#include <game/rendering/shader-binding.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

namespace sf {
    class Shader;
}

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getStandardTexturedSurfaceShader();

    void
    setTextureForStandardTexturedShader(
        ShaderBinding       binding,
        const sf::Texture&  texture
    );
}
