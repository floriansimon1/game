#include <game/math/direction.hpp>

#include <game/math/constants.hpp>

namespace game::math {
    bool
    hasCardinalDirection(
        const CardinalDirection fullDirection,
        const CardinalDirection queriedDirection
    ) {
        using FlagType = std::underlying_type_t<CardinalDirection>;

        return static_cast<FlagType>(fullDirection) & static_cast<FlagType>(queriedDirection);
    }

    CardinalDirection
    trigonometricAngleToCardinalDirection(
        const float angle
    ) {
        const float normalizedAngle = fmodf(angle + game::math::completePeriod, game::math::completePeriod);

        const float isPureDirection = fmod(normalizedAngle, game::math::halfPeriod) == 0.f;

        if (isPureDirection) {
            return static_cast<CardinalDirection>(1 + static_cast<unsigned>(normalizedAngle / game::math::quarterPeriod));
        }

        const bool  north           = normalizedAngle < game::math::halfPeriod;
        const bool  west            = normalizedAngle > game::math::quarterPeriod && normalizedAngle < game::math::halfPeriod + game::math::quarterPeriod;

        return static_cast<CardinalDirection>(
            static_cast<unsigned>(north ? CardinalDirection::north : CardinalDirection::south)
            | static_cast<unsigned>(west ? CardinalDirection::west : CardinalDirection::east)
        );
    }

    const char*
    cardinalDirectionToString(
        const CardinalDirection direction
    ) {
        switch (direction) {
            case CardinalDirection::east:      return "east";
            case CardinalDirection::west:      return "west";
            case CardinalDirection::north:     return "north";
            case CardinalDirection::south:     return "south";
            case CardinalDirection::northEast: return "north east";
            case CardinalDirection::southEast: return "south east";
            case CardinalDirection::northWest: return "north west";
            case CardinalDirection::southWest: return "south west";
        }

        return ""; // Silences warnings.
    }

    static DimensionΔ
    get2dDimensionΔ(
        const Direction2d direction
    ) {
        return direction == Direction2d::up || direction == Direction2d::left ? -1 : 1;
    }

    bool
    isXDirection(
        const Direction2d   direction
    ) {
        return direction == Direction2d::left || direction == Direction2d::right;
    }

    bool
    isYDirection(
        const Direction2d   direction
    ) {
        return !isXDirection(direction);
    }

    static std::optional<Dimension>
    bounded2dDirectionComponentIncrease(
        const Dimension  maximum,
        const DimensionΔ Δ,
        const Dimension  component
    ) {
        if (
            (component == 0 && Δ == -1)
            || (component == maximum -1 && Δ == 1)
        ) {
            return std::nullopt;
        }

        return static_cast<Dimension>(component + Δ);
    }

    std::optional<Dimension>
    incrementBounded2dX(
        const Dimension     width,
        const Direction2d   direction,
        const Dimension     x
    ) {
        if (isYDirection(direction)) {
            return x;
        }

        return bounded2dDirectionComponentIncrease(width, get2dDimensionΔ(direction), x);
    }
    
    std::optional<Dimension>
    incrementBounded2dY(
        const Dimension     height,
        const Direction2d   direction,
        const Dimension     y
    ) {
        if (isXDirection(direction)) {
            return y;
        }

        return bounded2dDirectionComponentIncrease(height, get2dDimensionΔ(direction), y);
    }
}
