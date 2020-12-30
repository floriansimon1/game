#include <game/rendering/camera.hpp>

#include <game/base/iterable-to-optional.hpp>

#include <game/ecs/scene.hpp>
#include <game/ecs/transform.hpp>

#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>

namespace game::rendering {
    Camera::Camera(
        const float aspectRatio
    )
    : projection(glm::perspective(glm::radians(50.0f), aspectRatio, 0.1f, 100.0f))
    {}

    std::optional<glm::mat4>
    getFirstCameraProjectionViewMatrix(game::ecs::Scene& scene) {
        return scene
        .findEntitiesWithComponent<Camera>()
        | ranges::views::for_each([] (const auto cameraEntityComponent) {
            const auto [cameraEntity, cameraComponent] = cameraEntityComponent;

            return cameraEntity
            ->template findComponents<game::ecs::Transform>()
            | ranges::views::transform([cameraComponent] (const auto transformComponent) {
                return cameraComponent->projection * transformComponent->quaternion;
            });
        })
        | game::base::toOptional();
    }
}
