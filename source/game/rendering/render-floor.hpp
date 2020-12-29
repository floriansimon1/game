#pragma once

#include <memory>

namespace game::ecs {
    class Scene;
}

namespace game::rendering {
    class Camera;

    void
    renderFloor(
        game::ecs::Scene& scene
    );
}
