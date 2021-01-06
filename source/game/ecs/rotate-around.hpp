#pragma once

#include <game/math/direction.hpp>

#include <game/ecs/component.hpp>

#include <glm/vec3.hpp>

#include <chrono>

namespace game::ecs {
    class Scene;

    class RotateAround
    : public game::ecs::Component {
        public:
            RotateAround(
                const float       speed,
                const float       height,
                const glm::vec3   center,
                const float       circleAmplitude
            );

            game::math::CardinalDirection
            getCardinalDirection() const;

            float                       speed;
            float                       height;
            glm::vec3                   center;
            float                       currentAngle;
            float                       circleAmplitude;
    };

    void
    rotateAround(
        Scene&                          scene,
        const std::chrono::milliseconds Δt
    );
}
