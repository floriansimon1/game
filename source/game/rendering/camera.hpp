#pragma once

#include <game/ecs/component.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <optional>

namespace game::ecs {
    class Scene;
}

namespace game::rendering {
    class Camera
    : public game::ecs::Component {
        public:
            Camera(
                const float aspectRatio
            );

            glm::mat4 projection;
    };
    
    std::optional<glm::mat4>
    getFirstCameraProjectionViewMatrix(game::ecs::Scene& scene);
}
