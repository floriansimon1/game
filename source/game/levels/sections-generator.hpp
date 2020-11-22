#pragma once

#include <game/math/random.hpp>
#include <game/math/dimensions.hpp>

#include <game/levels/level-section.hpp>

namespace game::levels {
    [[nodiscard]] LevelSection
    generate(
        const game::math::Dimension                         width,
        const game::math::Dimension                         height,
        game::math::random::ReproducibleDimensionGenerator& random
    );
}
