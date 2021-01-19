#pragma once

#include <game/math/dimensions.hpp>

#include <cassert>
#include <cstddef>
#include <optional>
#include <type_traits>

namespace game::math {
    using ByteUnderlyingType = std::underlying_type_t<std::byte>;

    enum class CardinalDirection: ByteUnderlyingType {
        east  = 0b0001,
        north = 0b0010,
        west  = 0b0100,
        south = 0b1000,

        northWest = static_cast<ByteUnderlyingType>(CardinalDirection::north) | static_cast<ByteUnderlyingType>(CardinalDirection::west),
        northEast = static_cast<ByteUnderlyingType>(CardinalDirection::north) | static_cast<ByteUnderlyingType>(CardinalDirection::east),
        southWest = static_cast<ByteUnderlyingType>(CardinalDirection::south) | static_cast<ByteUnderlyingType>(CardinalDirection::west),
        southEast = static_cast<ByteUnderlyingType>(CardinalDirection::south) | static_cast<ByteUnderlyingType>(CardinalDirection::east)
    };

    bool
    hasCardinalDirection(
        const CardinalDirection fullDirection,
        const CardinalDirection queriedDirection
    );

    CardinalDirection
    trigonometricAngleToCardinalDirection(
        const float angle
    );

    const char*
    cardinalDirectionToString(
        const CardinalDirection direction
    );

    enum class Direction2d: std::underlying_type_t<std::byte> {
        up    = 0b1000,
        down  = 0b0100,
        left  = 0b0010,
        right = 0b0001
    };

    bool
    isXDirection(
        const Direction2d   direction
    );

    bool
    isYDirection(
        const Direction2d   direction
    );

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
