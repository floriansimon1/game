#pragma once

#include <game/math/random.hpp>

#include <map>
#include <algorithm>

namespace game::math::random {
    template<typename Integer>
    Reproducible<Integer>::Reproducible(
        Integer seed
    )
        : engine(seed)
    {}

    // See https://stackoverflow.com/questions/19036141/vary-range-of-uniform-int-distribution
    // and https://stackoverflow.com/questions/30103356/distributions-and-internal-state
    template<typename Integer>
    template <typename Distribution, typename... Parameters>
    Distribution
    Reproducible<Integer>::getDistribution(const Parameters... parameters) {
        return Distribution(parameters...);
    }

    template<typename Integer>
    bool
    Reproducible<Integer>::boolean(
        Probability     probability
    ) {
        auto distribution = this->getDistribution<std::bernoulli_distribution>(probability);

        return distribution(this->engine);
    }

    template<typename Integer>
    Integer
    Reproducible<Integer>::binomial(
        Integer         inclusiveMinimum,
        Integer         inclusiveMaximum,
        Probability     probability
    ) {
        auto distribution = this->getDistribution<std::binomial_distribution<Integer>>(inclusiveMaximum - inclusiveMinimum, probability);

        return distribution(this->engine) + inclusiveMinimum;
    }

    template<typename Integer>
    Integer
    Reproducible<Integer>::uniform(
        Integer         inclusiveMinimum,
        Integer         inclusiveMaximum
    ) {
        auto distribution = this->getDistribution<std::uniform_int_distribution<Integer>>(inclusiveMinimum, inclusiveMaximum);

        return distribution(this->engine);
    }

    template<typename Integer>
    template<typename Container>
    void
    Reproducible<Integer>::shuffle(
        Container&   container
    ) {
        std::shuffle(container.begin(), container.end(), this->engine);
    }
}
