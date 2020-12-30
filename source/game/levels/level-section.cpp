#include <game/levels/level-section.hpp>

namespace game::levels {
    LevelSection::LevelSection(
        const game::math::Dimension                           width,
        const game::math::Dimension                           height,
        game::math::SequenceGenerator<game::math::Dimension>& idGenerator
    )
        : id(idGenerator.next())
        , width(width)
        , height(height)
    {}

    void
    LevelSection::split(
        const bool                                            splitHorizontally,
        const game::math::Dimension                           cuttingPoint,
        game::math::SequenceGenerator<game::math::Dimension>& idGenerator
    ) {
        this->splitHorizontally = splitHorizontally;

        this->subsection1 = std::make_shared<LevelSection>(
            splitHorizontally ? this->width                   : cuttingPoint,
            splitHorizontally ? cuttingPoint                  : this->height,
            idGenerator
        );

        this->subsection2 = std::make_shared<LevelSection>(
            splitHorizontally ? this->width                   : this->width - cuttingPoint,
            splitHorizontally ? this->height - cuttingPoint   : this->height,
            idGenerator
        );
    }

    bool
    LevelSection::isTerminal() const {
        return this->subsection1 == nullptr;
    }

    void
    LevelSection::writeSectionIds(
        Level&                                                level,
        const game::math::Dimension                           xOffset,
        const game::math::Dimension                           yOffset
    ) const {
        if (this->isTerminal()) {
            for (game::math::Dimension x = xOffset; x < xOffset + this->width; x++) {
                for (game::math::Dimension y = yOffset; y < yOffset + this->height; y++) {
                    level.getWriteableTile(x, y)->sectionId = this->id;
                }
            }
        } else {
            this->subsection1->writeSectionIds(level, xOffset, yOffset);

            this->subsection2->writeSectionIds(
                level,
                xOffset + (this->splitHorizontally   ? 0                         : this->subsection1->width),
                yOffset + (this->splitHorizontally   ? this->subsection1->height : 0)
            );
        }
    }

    Level
    LevelSection::toLevel() const {
        Level level(this->width, this->height);

        this->writeSectionIds(level, 0u, 0u);

        return level;
    }
}
