#pragma once

#include <game/ecs/component.hpp>

#include <glm/gtx/euler_angles.hpp>

namespace game::ecs {
    class Transform
    : public game::ecs::Component
    {
        public:
            glm::vec3 position    = glm::vec3(0.f, 0.f, 0.f);
            glm::mat4 orientation = glm::eulerAngleX(0.0f);

            glm::mat4
            getMatrix() const;
    };
}
