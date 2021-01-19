#pragma once

#include <game/math/random.hpp>

#include <memory>

namespace game::levels {
    class Level;

    void
    addRelief(
        std::shared_ptr<Level>                              level,
        game::math::random::ReproducibleDimensionGenerator& randomGenerator
    );
}
