#include <game/ecs/component.hpp>

#include <glm/gtc/type_ptr.hpp>

namespace game::ecs {
    class Transform
    : public game::ecs::Component
    {
        public:
            glm::mat4 quaternion;
    };
}
