#pragma once

#include <chrono>
#include <memory>

namespace game::ecs {
    class Scene;
}

namespace game::rendering {
    void
    renderFloor(
        game::ecs::Scene&               scene,
        const std::chrono::milliseconds 
    );
}
