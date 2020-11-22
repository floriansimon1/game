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

    std::vector<game::math::Rectangle>
    LevelSection::asRectangles() const
    {
        std::vector<game::math::Rectangle> list;

        this->asRectangles(list, 0u, 0u);

        return list;
    }

    void
    LevelSection::asRectangles(
        std::vector<game::math::Rectangle>&     rectangles,
        const game::math::Dimension             xOffset,
        const game::math::Dimension             yOffset
    ) const {
        if (this->isTerminal()) {
            rectangles.emplace_back(xOffset, yOffset, this->width, this->height);

            return;
        }

        this->subsection1->asRectangles(rectangles, xOffset, yOffset);

        this->subsection2->asRectangles(
            rectangles,
            xOffset + (this->splitHorizontally   ? 0                         : this->subsection1->width),
            yOffset + (this->splitHorizontally   ? this->subsection1->height : 0)
        );
    }
}
