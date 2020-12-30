#pragma once

#include <game/math/dimensions.hpp>

#include <game/ecs/component.hpp>

#include <SFML/Graphics/Color.hpp>

namespace game::levels {
    using SectionId = game::math::Dimension;

    class Tile: public game::ecs::Component {
        public:
            Tile(
                game::math::Dimension x,
                game::math::Dimension y
            );

            game::math::Dimension x;
            game::math::Dimension y;
            sf::Color             color;
            game::math::Dimension height;
            SectionId             sectionId;
    };
}
