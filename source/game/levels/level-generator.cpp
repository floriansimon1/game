#include <game/math/sequence-generator.hpp>

#include <game/levels/sections-generator.hpp>
#include <game/levels/level-generator.hpp>
#include <game/levels/level.hpp>

namespace game::levels {
    [[nodiscard]] Level
    generate(
        const game::math::Dimension width,
        const game::math::Dimension height
    ) {
        const auto section = SectionsGenerator::generate(width, height);
    }
}
