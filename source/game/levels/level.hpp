#pragma once

#include <game/math/dimensions.hpp>

#include <game/levels/tile.hpp>

#include <vector>

namespace game::levels {
    class Level {
        private:
            std::vector<game::levels::Tile> tiles;

            game::math::Dimension
            getOffset(
                const game::math::Dimension   x,
                const game::math::Dimension   y
            ) const;

        public:
            const game::math::Dimension   width;
            const game::math::Dimension   height;

            Level(
                const game::math::Dimension    width,
                const game::math::Dimension    height
            );

            void
            write(
                const game::math::Dimension   x,
                const game::math::Dimension   y,
                const game::math::Dimension   value
            );

            game::math::Dimension
            read(
                const game::math::Dimension   x,
                const game::math::Dimension   y
            ) const;
    };
}
