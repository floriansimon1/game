#pragma once

#include <chrono>

namespace game::ecs {
    class Component {
        public:
            virtual
            ~Component();

            virtual void
            update(
                const std::chrono::milliseconds Δt
            ) = 0;
    };
}
