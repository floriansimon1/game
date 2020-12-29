#pragma once

#include <SFML/Graphics/Color.hpp>

#include <vector>

namespace game::rendering {
    std::vector<sf::Color>
    getDistinctColorsArray(
        const unsigned numberOfColors
    );
}