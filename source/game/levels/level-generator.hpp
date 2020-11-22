#pragma once

#include <game/math/dimensions.hpp>

#include <game/levels/level.hpp>

namespace game::levels {
    [[nodiscard]] Level
    generate(
        const game::math::Dimension width,
        const game::math::Dimension height
    );
}
