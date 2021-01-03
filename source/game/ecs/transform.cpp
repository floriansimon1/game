#include <game/ecs/transform.hpp>

#include <glm/gtx/transform.hpp>

namespace game::ecs {
    glm::mat4
    Transform::getMatrix() const {
        return glm::translate(this->position) * this->orientation;
    }
}
