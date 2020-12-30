#include <game/ecs/transform.hpp>

namespace game::ecs {
    Transform::Transform(
        glm::mat4&& quaternion
    )
    : quaternion(quaternion)
    {}
}
