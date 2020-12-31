#pragma once

#include <game/math/dimensions.hpp>

#include <cstddef>
#include <optional>
#include <type_traits>

namespace game::math {
    enum class Direction2d: std::underlying_type_t<std::byte> {
        up    = 0b1000,
        down  = 0b0100,
        left  = 0b0010,
        right = 0b0001
    };

    std::optional<Dimension>
    incrementBounded2dX(
        const Dimension     width,
        const Direction2d   direction,
        const Dimension     x
    );
    
    std::optional<Dimension>
    incrementBounded2dY(
        const Dimension     height,
        const Direction2d   direction,
        const Dimension     y
    );
}
