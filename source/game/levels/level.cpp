#include <game/levels/level.hpp>

namespace game::levels {
    game::math::Dimension
    Level::getOffset(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) const {
        return x * this->width + y;
    }

    void
    Level::write(
        const game::math::Dimension   x,
        const game::math::Dimension   y,
        const game::math::Dimension   value
    ) {
        this->tiles[this->getOffset(x, y)] = value;
    }

    game::math::Dimension
    Level::read(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) const {
        return this->tiles[this->getOffset(x, y)];
    }

    Level::Level(
        const game::math::Dimension    width,
        const game::math::Dimension    height
    )
        : width(width)
        , height(height)
        , tiles(static_cast<size_t>(width * height))
    {}
};
