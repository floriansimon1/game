#pragma once

#include <game/rendering/shader-binding.hpp>

#include <SFML/Graphics/Color.hpp>

#include <memory>

namespace sf {
    class Shader;
}

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getForcedVertexColorShader();

    void
    setForcedVertexColorShader(
        ShaderBinding       binding,
        const sf::Color&    forcedColor
    );
}
