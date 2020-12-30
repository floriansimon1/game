#pragma once

#include <chrono>
#include <functional>

namespace game::ecs {
    class Scene;

    using System = std::function<void (Scene&, std::chrono::milliseconds)>;
}
