#pragma once

#include <game/math/random.hpp>

namespace game::levels {
    class Level;

    void
    addRelief(
        Level&                                              level,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    );
}
