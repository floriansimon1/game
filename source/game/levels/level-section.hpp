#pragma once

#include <game/math/sequence-generator.hpp>
#include <game/math/dimensions.hpp>

#include <game/levels/level.hpp>

#include <cstdint>
#include <memory>
#include <vector>

namespace game::levels {
    class LevelSection {
        public:
            const game::math::Dimension             id;
            game::math::Dimension                   width;
            game::math::Dimension                   height;
            std::shared_ptr<LevelSection>           subsection1;
            std::shared_ptr<LevelSection>           subsection2;
            bool                                    splitHorizontally;

                                                    LevelSection(
                                                        const game::math::Dimension                           width,
                                                        const game::math::Dimension                           height,
                                                        game::math::SequenceGenerator<game::math::Dimension>& idGenerator
                                                    );

            void                                    split(
                                                        const bool                                            splitHorizontally,
                                                        const game::math::Dimension                           cuttingPoint,
                                                        game::math::SequenceGenerator<game::math::Dimension>& idGenerator
                                                    );

            bool                                    isTerminal() const;

            Level                                   toLevel() const;

        private:
            void                                    writeSectionIds(
                                                        Level&                                                level,
                                                        const game::math::Dimension                           xOffset,
                                                        const game::math::Dimension                           yOffset
                                                    ) const;
    };
}
