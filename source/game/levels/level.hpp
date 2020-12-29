#pragma once

#include <game/math/dimensions.hpp>

#include <game/levels/tile.hpp>

#include <vector>

int main(int, char**);

namespace game::levels {
    class Level {
        private:
            std::vector<Tile>                  tiles;

            game::math::Dimension
            getOffset(
                const game::math::Dimension   x,
                const game::math::Dimension   y
            ) const;

        public:
            const game::math::Dimension        width;
            const game::math::Dimension        height;

            Level(
                const game::math::Dimension    width,
                const game::math::Dimension    height
            );

            Tile&
            getWriteableTile(
                const game::math::Dimension   x,
                const game::math::Dimension   y
            );

            friend int ::main(int, char**);
    };
}
