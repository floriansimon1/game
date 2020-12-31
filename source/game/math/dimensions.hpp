#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <cstdint>
#include <type_traits>

namespace game::math {
    using Dimension = unsigned int;

    using DimensionΔ = std::make_signed_t<Dimension>;

    using Rectangle = sf::Rect<Dimension>;
}
