#include <game/ecs/spin.hpp>

#include <game/ecs/scene.hpp>
#include <game/ecs/transform.hpp>

namespace game::ecs {
    Spinning::Spinning(
        float       speed,
        glm::vec3   axis
    )
    : speed(speed)
    , axis(axis)
    {}

    void
    spin(
        Scene&                          scene,
        const std::chrono::milliseconds Δt
    ) {
        for (const auto [entity, transformComponent, spinningComponent]: scene.findEntitiesWithComponents<Transform, Spinning>()) {
            const auto angle = spinningComponent->speed * 2.f * static_cast<float>(M_PI) * (static_cast<float>(Δt.count()) / 1000.f);

            transformComponent->quaternion = glm::rotate(transformComponent->quaternion, angle, spinningComponent->axis);
        }
    }
}
