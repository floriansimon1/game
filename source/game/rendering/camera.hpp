#pragma once

#include <game/ecs/component.hpp>
#include <game/ecs/transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <optional>
#include <memory>

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

    class CameraState {
        public:
            game::ecs::Transform&   transform;
            Camera&                 camera;

            glm::mat4
            getProjectionViewMatrix() const;
    };

    std::optional<CameraState>
    computeFirstCameraState(game::ecs::Scene& scene);
}
