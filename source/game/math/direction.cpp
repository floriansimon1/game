#include <game/math/direction.hpp>

namespace game::math {
    static DimensionΔ
    get2dDimensionΔ(
        const Direction2d direction
    ) {
        return direction == Direction2d::up || direction == Direction2d::left ? -1 : 1;
    }

    static bool
    isXDirection(
        const Direction2d   direction
    ) {
        return direction == Direction2d::left || direction == Direction2d::right;
    }

    static bool
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
