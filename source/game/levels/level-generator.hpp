#pragma once

#include <game/math/dimensions.hpp>
#include <game/math/random.hpp>

#include <game/levels/level.hpp>

namespace game::levels {
    std::shared_ptr<Level>
    generateLevel(
        const game::math::Dimension                         width,
        const game::math::Dimension                         height,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    );
}
