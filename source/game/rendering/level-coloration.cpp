#include <game/rendering/level-coloration.hpp>

#include <game/levels/level.hpp>

#include <game/rendering/colors.hpp>

namespace game::rendering {
    void
    colorizeLevel(game::levels::Level& level) {
        const auto maxSectionId = level.getMaximumSectionId();

        const auto colors       = game::rendering::getDistinctColorsArray(maxSectionId + 1);

        for (game::math::Dimension x = 0u; x < level.width; x++) {
            for (game::math::Dimension y = 0u; y < level.height; y++) {
                auto tile = level.getWriteableTile(x, y);

                tile->color = colors[tile->sectionId % maxSectionId];
            }
        }
    }
}
