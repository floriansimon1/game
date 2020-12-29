#pragma once

#include <game/math/dimensions.hpp>

namespace game::levels {
    using SectionId = game::math::Dimension;

    class Tile {
        public:
            game::math::Dimension   height      = rand() % 3;
            SectionId               sectionId;
    };
}