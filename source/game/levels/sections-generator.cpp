#include <game/levels/sections-generator.hpp>

#include <game/math/sequence-generator.hpp>

#include <game/levels/tile.hpp>
#include <game/levels/level-section.hpp>

using game::math::Dimension;
using game::math::random::ReproducibleDimensionGenerator;

static inline game::math::random::Probability
computeSectionTerminalityProbability(
    const Dimension                         parentSubdivisionsCount 
) {
    if (parentSubdivisionsCount < 5) {
        return 0.0;
    }

    return std::min(1.0, static_cast<double>(parentSubdivisionsCount) * 0.05f);
}

namespace game::levels {
    static void
    subdivide(
        LevelSection&                               subsectionToConfigure,
        const game::math::Dimension                 parentSubdivisionsCount,
        ReproducibleDimensionGenerator&             random,
        game::math::SequenceGenerator<SectionId>&   sequence
    ) {
        const bool canSplitHorizontally = subsectionToConfigure.height > 1u;
        const bool canSplitVertically   = subsectionToConfigure.width > 1u;

        if (!(canSplitHorizontally || canSplitVertically)) {
            return;
        }

        const bool isTerminal = random.boolean(computeSectionTerminalityProbability(parentSubdivisionsCount));

        if (isTerminal) {
            return;
        }

        const bool      splitHorizontally   = canSplitVertically && canSplitHorizontally ? random.boolean(game::math::random::even) : canSplitHorizontally;

        const Dimension cuttingPoint        = random.binomial(1, (splitHorizontally ? subsectionToConfigure.height : subsectionToConfigure.width) - 1, game::math::random::even);

        subsectionToConfigure.split(splitHorizontally, cuttingPoint, sequence);

        subdivide(*subsectionToConfigure.subsection1, parentSubdivisionsCount + 1, random, sequence);
        subdivide(*subsectionToConfigure.subsection2, parentSubdivisionsCount + 1, random, sequence);
    }

    [[nodiscard]] LevelSection
    generateSections(
        const Dimension                     width,
        const Dimension                     height,
        ReproducibleDimensionGenerator&     random
    ) {
        game::math::SequenceGenerator<SectionId> sequence;

        auto                                     section  = LevelSection(width, height, sequence);

        subdivide(section, 0, random, sequence);

        return section;
    }
}

