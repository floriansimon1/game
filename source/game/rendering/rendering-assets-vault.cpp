#include <game/rendering/rendering-assets-vault.hpp>

#include <game/ecs/scene.hpp>

#include <game/base/iterable-to-optional.hpp>

#include <range/v3/view/map.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>

namespace game::rendering {
    class Mesh;

    std::optional<std::reference_wrapper<Mesh>>
    findMeshInFirstRenderingAssetsVault(
        game::ecs::Scene&   scene,
        const std::string&  name
    ) {
        const auto vault = scene.getFirstComponent<RenderingAssetsVault>();

        if (!vault) {
            return std::nullopt;
        }

        const auto iterator = (*vault)->meshes.find(name);

        if (iterator == (*vault)->meshes.end()) {
            return std::nullopt;
        }

        return std::ref(iterator->second);
    }
}
