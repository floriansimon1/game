#include <game/math/sequence-generator.hpp>

#include <game/levels/sections-generator.hpp>
#include <game/levels/relief-generator.hpp>
#include <game/levels/level-generator.hpp>

namespace game::levels {
    std::shared_ptr<Level>
    generateLevel(
        const game::math::Dimension                         width,
        const game::math::Dimension                         height,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    ) {
        auto level = std::make_shared<Level>(generateSections(width, height, randomGenerator).toLevel());

        addRelief(level, randomGenerator);

        return level;
    }
}
