#include <game/levels/tile.hpp>

namespace game::levels {
    Tile::Tile(
        game::math::Dimension x,
        game::math::Dimension y
    )
    : x(x)
    , y(y)
    , height(0)
    {}
}
