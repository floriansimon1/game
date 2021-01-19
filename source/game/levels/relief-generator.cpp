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
            const std::shared_ptr<Level>&                       level;

            AlgorithmCache(
                const std::shared_ptr<Level> level,
                Tile&                        startTile
            )
            : heightTable(level->getMaximumSectionId() + 1)
            , level(level)
            {
                // This makes sure we can never go below 0 in height.
                this->heightTable[startTile.sectionId] = std::max(level->width, level->height);
            }
    };

    static game::math::Dimension
    pickHeight(
        game::math::random::ReproducibleDimensionGenerator& randomGenerator,
        AlgorithmCache&                                     cache,
        const Tile&                                         tile
    ) {
        std::vector<game::math::Dimension> surroundingHeights;
 
        for (game::math::Dimension x = std::max<int>(0, tile.x - 1); x <= std::min(tile.x + 1, cache.level->width - 1); x++) {
            for (game::math::Dimension y = std::max<int>(0, tile.y - 1); y <= std::min(tile.y + 1, cache.level->height - 1); y++) {
                const auto neighbor = cache.level->getWriteableTile(x, y);

                if (cache.heightTable[neighbor->sectionId].has_value()) {
                    surroundingHeights.push_back(cache.heightTable[neighbor->sectionId].value());
                }
            }
        }

        const auto flooredAverage = std::accumulate(surroundingHeights.cbegin(), surroundingHeights.cend(), 0) / surroundingHeights.size();

        if (randomGenerator.boolean(game::math::random::even)) {
            return flooredAverage;
        }

        const int Δheight = randomGenerator.boolean(game::math::random::even) ? 1 : -1;

        return flooredAverage + Δheight;
    }

    static void
    calculateHeight(
        game::math::random::ReproducibleDimensionGenerator& randomGenerator,
        std::shared_ptr<Level>                              level,
        AlgorithmCache&                                     cache,
        game::math::Dimension                               x,
        game::math::Dimension                               y
    ) {
        auto& tile = *level->getWriteableTile(x, y);

        if (cache.heightTable[tile.sectionId].has_value()) {
            tile.height = cache.heightTable[tile.sectionId].value();

            return;
        }

        tile.height = pickHeight(randomGenerator, cache, tile);

        cache.heightTable[tile.sectionId].emplace(tile.height);
    }

    static void
    addRelief(
        game::math::random::ReproducibleDimensionGenerator& randomGenerator,
        std::shared_ptr<Level>                              level,
        game::math::Direction2d                             direction,
        AlgorithmCache&                                     cache,
        game::math::Dimension                               x,
        game::math::Dimension                               y
    ) {
        calculateHeight(randomGenerator, level, cache, x, y);

        const auto incrementedX = game::math::incrementBounded2dX(level->width,  direction, x);
        const auto incrementedY = game::math::incrementBounded2dY(level->height, direction, y);

        if (incrementedX.has_value() && incrementedY.has_value()) {
            addRelief(randomGenerator, level, direction, cache, incrementedX.value(), incrementedY.value());
        }
    }

    static void
    addRelief(
        game::math::random::ReproducibleDimensionGenerator& randomGenerator,
        std::shared_ptr<Level>                              level,
        game::math::Direction2d                             firstDirection,
        game::math::Direction2d                             secondDirection,
        AlgorithmCache&                                     cache,
        game::math::Dimension                               x,
        game::math::Dimension                               y
    ) {
        calculateHeight(randomGenerator, level, cache, x, y);

        const auto incrementedX = game::math::incrementBounded2dX(level->width,  firstDirection, x);
        const auto incrementedY = game::math::incrementBounded2dY(level->height, firstDirection, y);

        if (incrementedX.has_value() && incrementedY.has_value()) {
            addRelief(randomGenerator, level, firstDirection, secondDirection, cache, incrementedX.value(), incrementedY.value());
        }

        addRelief(randomGenerator, level, secondDirection, cache, x, y);
    }

    void
    addRelief(
        std::shared_ptr<Level>                              level,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    ) {
        const game::math::Dimension halfOfWidth  = level->width / 2;
        const game::math::Dimension halfOfHeight = level->height / 2;

        const auto startingPointX = (randomGenerator.binomial(0, level->width,  game::math::random::even) + halfOfWidth) % level->width;
        const auto startingPointY = (randomGenerator.binomial(0, level->height, game::math::random::even) + halfOfHeight) % level->height;

        const auto startTile = level->getWriteableTile(startingPointX, startingPointY);

        AlgorithmCache cache(level, *startTile);

        // The helix-shaped traversal pattern allows us to not keep track of traversed elements.
        addRelief(randomGenerator, level, game::math::Direction2d::up,    game::math::Direction2d::left,  cache, startingPointX, startingPointY);
        addRelief(randomGenerator, level, game::math::Direction2d::right, game::math::Direction2d::up,    cache, startingPointX, startingPointY);
        addRelief(randomGenerator, level, game::math::Direction2d::down,  game::math::Direction2d::right, cache, startingPointX, startingPointY);
        addRelief(randomGenerator, level, game::math::Direction2d::left,  game::math::Direction2d::down,  cache, startingPointX, startingPointY);

        const auto minimumLevel = std::ranges::min(
            level->getTilesView(),
            [] (const auto& tileA, const auto& tileB) { return tileA->height < tileB->height; }
        )
        .get()
        ->height;

        for (const auto& tile: level->getTilesView()) {
            tile->height -= minimumLevel;
        }
    }
}