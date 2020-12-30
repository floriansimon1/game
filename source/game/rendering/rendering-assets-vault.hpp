#pragma once

#include <game/rendering/mesh.hpp>

#include <game/ecs/component.hpp>

#include <map>
#include <string>
#include <optional>

namespace game::ecs {
    class Scene;
}

namespace game::rendering {
    class Mesh;

    class RenderingAssetsVault: public game::ecs::Component {
        public:
            std::map<std::string, Mesh> meshes;
    };

    std::optional<std::reference_wrapper<Mesh>>
    findMeshInFirstRenderingAssetsVault(
        game::ecs::Scene&   scene,
        const std::string&  name
    );
}