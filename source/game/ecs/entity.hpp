#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <coro/shared_generator.h>

#include <memory>
#include <vector>
#include <concepts>

namespace game::ecs {
    class Component;

    class Entity {
        public:
            glm::mat4                               model;
            std::vector<std::shared_ptr<Component>> components;

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
    };
}
