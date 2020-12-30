#pragma once

#include <chrono>

namespace game::ecs {
    class Component {
        public:
            virtual
            ~Component() {};
    };
}
