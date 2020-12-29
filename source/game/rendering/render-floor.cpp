#include <game/rendering/camera.hpp>

namespace game::rendering {
    void
    renderFloor(game::ecs::Scene& scene) {
        const auto projectionViewMatrix = getFirstCameraProjectionViewMatrix(scene);

        if (!projectionViewMatrix) {
            return;
        }

        // | ranges::views::for_each([&cameraComponent] (const auto [entity, component]) {
        //     cameraComponent = component;
        //     cameraEntity    = entity;
        // });

        // if (cameraEntity == nullptr) {
        //     return;
        // }

        // cameraEntity
        // ->findComponent<game::ecs::Transform>();
        // | ranges::views::take(1)
        // | ranges::views::

        //     return entity
        //     ->findComponent<game::ecs::Transform>();
        //     | ranges::views::take(1)
        //     | ranges::veiws::transform([&entity, &cameraComponent] (conat auto transformComponent) {
        //         return std::make_tuple(entity, cameraComponent, transformComponent);
        //     });
        // });

        // glm::mat4 projectionViewMatrix;
        // bool        activeCameraFound = this->activeCamera->getProjectionViewMatrix();


        // for (const auto& entity: scene.entities) {
        //     for (const auto& component: entity->components) {
        //         const auto renderable = std::dynamic_pointer_cast<Renderable>(component);

        //         if (renderable == nullptr) {
        //             continue;
        //         }

        //         renderable->render(projectionViewMatrix);
        //     }
        // }
    }
}
