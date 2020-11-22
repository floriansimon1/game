#pragma once

#include <game/base/non-copyable.hpp>

#include <game/math/dimensions.hpp>

#include <random>

namespace game::math::random {
    using Probability = double;

    static constexpr Probability even = 0.5;

    template<typename Integer>
    class Reproducible: private game::base::NonCopyable {
        private:
            std::mt19937 engine;

            template <typename Distribution, typename... Parameters>
            Distribution
            getDistribution(const Parameters... parameters);
        
        public:
            Reproducible(
                Integer     seed
            );

            Integer
            binomial(
                Integer     inclusiveMinimum,
                Integer     inclusiveMaximum,
                Probability probability
            );

            Integer
            uniform(
                Integer     inclusiveMinimum,
                Integer     inclusiveMaximum
            );

            bool
            boolean(
                double      probability
            );

            template <typename Container>
            void
            shuffle(
                Container&  container
            );
    };

    using ReproducibleDimensionGenerator = game::math::random::Reproducible<game::math::Dimension>;
}


#include <game/math/random.implementation.hpp>
