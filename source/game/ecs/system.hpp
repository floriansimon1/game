#pragma once

#include <functional>

namespace game::ecs {
    class Scene;

    using System = std::function<void (Scene&)>;
}
