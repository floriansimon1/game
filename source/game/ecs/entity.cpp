#include <game/ecs/entity.hpp>

namespace game::ecs {
    std::shared_ptr<Entity>
    Entity::make(
        std::shared_ptr<Component> component
    ) {
        return Entity::make({ component });
    }

    std::shared_ptr<Entity>
    Entity::make(
        std::initializer_list<std::shared_ptr<Component>> components
    ) {
        auto entity = std::make_shared<game::ecs::Entity>();

        std::copy(components.begin(), components.end(), std::back_inserter(entity->components));

        return entity;
    }
}
