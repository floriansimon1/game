#include <game/rendering/camera.hpp>

#include <game/base/iterable-to-optional.hpp>

#include <game/ecs/scene.hpp>

namespace game::rendering {
    Camera::Camera(
        const float aspectRatio
    )
    : projection(glm::perspective(glm::radians(50.0f), aspectRatio, 0.1f, 200.0f))
    {}

    glm::mat4
    CameraState::getProjectionViewMatrix() const {
        return this->camera.projection * glm::inverse(this->transform.getMatrix());
    }

    std::optional<CameraState>
    computeFirstCameraState(game::ecs::Scene& scene) {
        const auto rawCameraState = scene.findEntitiesWithComponents<game::ecs::Transform, Camera>() | game::base::toOptional();

        if (rawCameraState == std::nullopt) {
            return std::nullopt;
        }

        return CameraState {
            .transform  = *std::get<1>(rawCameraState.value()),
            .camera     = *std::get<2>(rawCameraState.value())
        };
    }
}
