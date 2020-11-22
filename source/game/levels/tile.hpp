#pragma once

#include <game/math/dimensions.hpp>

namespace game::levels {
    using SectionId = game::math::Dimension;

    class Tile {
        public:
            SectionId sectionId;
    };
}