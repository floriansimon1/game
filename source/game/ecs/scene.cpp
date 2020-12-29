#include <game/ecs/scene.hpp>

namespace game::ecs {
    // Scene::Scene(
    //     const Camera& camera
    // )
    // : camera(camera)
    // , lastRenderedFrameTime(std::chrono::system_clock::now()) {}

    // std::chrono::milliseconds
    // Scene::update() {
    //     const auto frameTime = std::chrono::system_clock::now();

    //     const auto Δt        = std::chrono::duration_cast<std::chrono::milliseconds>(frameTime - lastRenderedFrameTime);

    //     this->camera.animate(Δt);

    //     for (const auto& renderObject: this->renderObjects) {
    //         renderObject->animate(Δt);
    //     }

    //     lastRenderedFrameTime = frameTime;

    //     return Δt;
    // }

    // void
    // Scene::render() {
    //     const auto projectionViewMatrix = this->camera.getProjectionViewMatrix();

    //     for (const auto& renderObject: this->renderObjects) {
    //         renderObject->draw(projectionViewMatrix);
    //     }
    // }
}
