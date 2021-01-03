#include <game/ecs/transform.hpp>

#include <glm/gtx/transform.hpp>

namespace game::ecs {
    glm::mat4
    Transform::getModelMatrix() const {
        return this->orientation * glm::translate(this->position);
    }
}
