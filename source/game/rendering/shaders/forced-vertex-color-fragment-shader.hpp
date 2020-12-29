#pragma once

#include <SFML/Graphics/Color.hpp>

#include <memory>

namespace sf {
    class Shader;
}

namespace game::rendering {
    std::unique_ptr<sf::Shader>
    getForcedVertexColorShader(
        const sf::Color forcedColor
    );
}
