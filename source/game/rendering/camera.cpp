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
            const auto cameraEntity    = cameraEntityComponent.first;
            const auto cameraComponent = cameraEntityComponent.second;

            return cameraEntity
            ->template findComponents<game::ecs::Transform>()
            | ranges::views::transform([cameraComponent] (const auto transformComponent) {
                return transformComponent->quaternion * cameraComponent->projection;
            });
        })
        | game::base::toOptional();
    }

    // , view(
    //     glm::lookAt(
    //         glm::vec3(0.0f, 30.0f, 30.0f), 
    //         glm::vec3(0.0f,  0.0f,  0.0f), 
    //         glm::vec3(0.0f,  1.0f,  0.0f)
    //     )

    // void
    // Camera::animate(
    //     const std::chrono::milliseconds Δt 
    // ) {
    //     constexpr auto roundsPerSecond = 0.05f;

    //     this->view = glm::rotate(this->view, roundsPerSecond * 2.f * static_cast<float>(M_PI) * (static_cast<float>(Δt.count()) / 1000.f), glm::vec3(0.f, 1.f, 0.f));
    // }

    // glm::mat4
    // Camera::getProjectionViewMatrix(
    //     const glm::mat4 modelMatrix
    // ) {
    //     return this->projection * modelMatrix;
    // }
}
