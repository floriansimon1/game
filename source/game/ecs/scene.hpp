#pragma once

#include <game/ecs/entity.hpp>

#include <coro/shared_generator.h>

#include <memory>
#include <vector>

namespace game::ecs {
    class Scene {
        public:
            std::vector<std::shared_ptr<Entity>>    entities;

            template <typename ComponentType>
            shared_generator<std::pair<std::shared_ptr<Entity>, std::shared_ptr<ComponentType>>>
            findEntitiesWithComponent() {
                for (auto entity: entities) {
                    auto componentsGenerator = entity->findComponents<ComponentType>();

                    for (auto component: componentsGenerator) {
                        co_yield { entity, component };
                    }
                }
            }
    };
}
