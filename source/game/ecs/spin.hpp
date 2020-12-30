#pragma once

#include <game/ecs/component.hpp>

#include <glm/vec3.hpp>

#include <chrono>

namespace game::ecs {
    class Scene;

    class Spinning
    : public game::ecs::Component {
        public:
            Spinning(
                float       speed,
                glm::vec3   axis
            );

            float       speed;
            glm::vec3   axis;
    };

    void
    spin(
        Scene&                          scene,
        const std::chrono::milliseconds Δt
    );
}
