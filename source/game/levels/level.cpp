#include <game/levels/level.hpp>

namespace game::levels {
    game::math::Dimension
    Level::getOffset(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) const {
        return x * this->width + y;
    }

    Tile&
    Level::getWriteableTile(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) {
        return this->tiles[this->getOffset(x, y)];
    }

    Level::Level(
        const game::math::Dimension    width,
        const game::math::Dimension    height
    )
        : tiles(static_cast<size_t>(width * height))
        , width(width)
        , height(height)
    {}
};
