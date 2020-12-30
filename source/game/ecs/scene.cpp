#include <game/ecs/scene.hpp>

namespace game::ecs {
    Scene::Scene(
        Scene&& scene
    )
    : entities(std::move(scene.entities))
    {}

    void
    Scene::process(
        std::chrono::milliseconds Δt
    ) {
        for (auto& system: this->systems) {
            system(*this, Δt);
        }
    }

    void
    Scene::addEntity(
        std::shared_ptr<Entity>   entity
    ) {
        this->entities.emplace_back(entity);
    }

    void
    Scene::addSystem(
        System                    system
    ) {
        this->systems.emplace_back(system);
    }
}
