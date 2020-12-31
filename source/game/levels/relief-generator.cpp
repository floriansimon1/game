#include <game/levels/relief-generator.hpp>

#include <game/levels/level.hpp>

#include <game/math/direction.hpp>

#include <vector>
#include <optional>
#include <algorithm>

namespace game::levels {
    class AlgorithmCache {
        public:
            std::vector<std::optional<game::math::Dimension>>   heightTable;

            AlgorithmCache(
                const Level&    level,
                Tile&           startTile
            )
            : heightTable(level.getMaximumSectionId())
            {
                // This makes sure we can never go below 0 in height.
                this->heightTable[startTile.sectionId] = std::max(level.width, level.height);
            }
    };

    static game::math::Dimension
    pickHeight() {
        return 5u + (rand() % 3u);
    }

    static void
    calculateHeight(
        Level&                  level,
        AlgorithmCache&         cache,
        game::math::Dimension   x,
        game::math::Dimension   y
    ) {
        auto& tile = *level.getWriteableTile(x, y);

        if (cache.heightTable[tile.sectionId].has_value()) {
            tile.height = cache.heightTable[tile.sectionId].value();

            return;
        }

        tile.height = pickHeight();

        cache.heightTable[tile.sectionId].emplace(tile.height);
    }

    static void
    addRelief(
        Level&                  level,
        game::math::Direction2d direction,
        AlgorithmCache&         cache,
        game::math::Dimension   x,
        game::math::Dimension   y
    ) {
        calculateHeight(level, cache, x, y);

        const auto incrementedX = game::math::incrementBounded2dX(level.width,  direction, x);
        const auto incrementedY = game::math::incrementBounded2dY(level.height, direction, y);

        if (incrementedX.has_value() && incrementedY.has_value()) {
            addRelief(level, direction, cache, incrementedX.value(), incrementedY.value());
        }
    }

    static void
    addRelief(
        Level&                  level,
        game::math::Direction2d firstDirection,
        game::math::Direction2d secondDirection,
        AlgorithmCache&         cache,
        game::math::Dimension   x,
        game::math::Dimension   y
    ) {
        calculateHeight(level, cache, x, y);

        const auto incrementedX = game::math::incrementBounded2dX(level.width,  firstDirection, x);
        const auto incrementedY = game::math::incrementBounded2dY(level.height, firstDirection, y);

        if (incrementedX.has_value() && incrementedY.has_value()) {
            addRelief(level, firstDirection, secondDirection, cache, incrementedX.value(), incrementedY.value());
        }

        addRelief(level, secondDirection, cache, x, y);
    }

    void
    addRelief(
        Level&                                              level,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    ) {
        const game::math::Dimension halfOfWidth  = level.width / 2;
        const game::math::Dimension halfOfHeight = level.height / 2;

        const auto startingPointX = (randomGenerator.binomial(0, level.width,  game::math::random::even) + halfOfWidth) % level.width;
        const auto startingPointY = (randomGenerator.binomial(0, level.height, game::math::random::even) + halfOfHeight) % level.height;

        const auto startTile = level.getWriteableTile(startingPointY, startingPointY);

        AlgorithmCache cache(level, *startTile);

        // The helix-shaped traversal pattern allows us to not keep track of traversed elements.
        addRelief(level, game::math::Direction2d::up,    game::math::Direction2d::left,  cache, startingPointX, startingPointY);
        addRelief(level, game::math::Direction2d::right, game::math::Direction2d::up,    cache, startingPointX, startingPointY);
        addRelief(level, game::math::Direction2d::down,  game::math::Direction2d::right, cache, startingPointX, startingPointY);
        addRelief(level, game::math::Direction2d::left,  game::math::Direction2d::down,  cache, startingPointX, startingPointY);

        const auto minimumLevel = std::ranges::min(
            level.getTilesView(),
            [] (const auto& tileA, const auto& tileB) { return tileA->height < tileB->height; }
        )
        .get()
        ->height;

        for (const auto& tile: level.getTilesView()) {
            tile->height -= minimumLevel;
        }
    }
}