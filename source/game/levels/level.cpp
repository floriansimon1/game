#include <game/levels/level.hpp>

#include <game/levels/level-section.hpp>

namespace game::levels {
    Level::Level(
        const game::math::Dimension    width,
        const game::math::Dimension    height
    )
    : tiles(static_cast<size_t>(width * height))
    , width(width)
    , height(height)
    {
        for (game::math::Dimension x = 0; x < width; x++) {
            for (game::math::Dimension y = 0; y < height; y++) {
                size_t i = getOffset(x, y);

                this->tiles[i] = std::make_shared<Tile>(x, y);
            }
        }
    }

    Level::Level(
        Level&&                         level
    )
    : tiles(std::move(level.tiles))
    , width(level.width)
    , height(level.height)
    {}

    game::math::Dimension
    Level::getOffset(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) const {
        return x * this->width + y;
    }

    std::shared_ptr<Tile>
    Level::getWriteableTile(
        const game::math::Dimension   x,
        const game::math::Dimension   y
    ) {
        return this->tiles[this->getOffset(x, y)];
    }

    SectionId
    Level::getMaximumSectionId() const {
        const auto maximumElement = *std::max_element(this->tiles.cbegin(), this->tiles.cend(), [] (const auto& a, const auto& b) {
            return a->sectionId < b->sectionId;
        });

        return maximumElement->sectionId;
    }
}
