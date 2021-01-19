#pragma once

#include <game/base/non-copyable.hpp>

#include <game/math/dimensions.hpp>

#include <game/levels/tile.hpp>

#include <vector>
#include <memory>
#include <ranges>

namespace game::levels {
    class Level: private game::base::NonCopyable, public game::ecs::Component {
        private:
            std::vector<std::shared_ptr<Tile>>  tiles;

            game::math::Dimension
            getOffset(
                const game::math::Dimension     x,
                const game::math::Dimension     y
            ) const;

        public:
            const game::math::Dimension         width;
            const game::math::Dimension         height;

            Level(
                const game::math::Dimension     width,
                const game::math::Dimension     height
            );

            Level(
                Level&&                         level
            );

            std::shared_ptr<Tile>
            getWriteableTile(
                const game::math::Dimension     x,
                const game::math::Dimension     y
            );

            SectionId
            getMaximumSectionId() const;

            std::ranges::ref_view<decltype(tiles)>
            getTilesView();
    };
}
