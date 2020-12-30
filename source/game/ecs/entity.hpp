#pragma once

#include <game/base/iterable-to-optional.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <coro/shared_generator.h>

#include <memory>
#include <vector>
#include <initializer_list>

namespace game::ecs {
    class Component;

    class Entity {
        private:
            /*
            * Encapsulating components here will allow me to refactor entity
            * storage to a less naive solution later.
            */
            std::vector<std::shared_ptr<Component>> components;

        public:
            static std::shared_ptr<Entity>
            make(
                std::shared_ptr<Component>                        component
            );

            static std::shared_ptr<Entity>
            make(
                std::initializer_list<std::shared_ptr<Component>> components
            );

            template <typename ComponentType>
            shared_generator<std::shared_ptr<ComponentType>>
            findComponents() {
                for (const auto& component: this->components) {
                    const auto targetComponent = std::dynamic_pointer_cast<ComponentType>(component);

                    if (targetComponent == nullptr) {
                        continue;
                    }

                    co_yield targetComponent;
                }
            }

            template <typename ComponentType>
            std::optional<std::shared_ptr<ComponentType>>
            findFirstComponent() {
                return this->findComponents<ComponentType>() | game::base::toOptional();
            }
    };
}
