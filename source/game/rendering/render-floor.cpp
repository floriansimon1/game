#include <game/rendering/shaders/forced-vertex-color-fragment-shader.hpp>

#include <game/rendering/rendering-assets-vault.hpp>
#include <game/rendering/unit-square.hpp>
#include <game/rendering/camera.hpp>

#include <game/levels/tile.hpp>
#include <game/levels/level.hpp>

#include <game/ecs/scene.hpp>

#include <glm/gtx/euler_angles.hpp>

#include <iostream>

namespace game::rendering {
    // Matrix calculations in here are easily memoized.
    static void
    renderFloorTile(
        const game::levels::LevelComponent& level,
        const game::levels::Tile&           tile,
        const glm::mat4&                    projectionViewMatrix,
        Mesh&                               mesh
    ) {
        const auto translatedX = static_cast<float>(tile.x) - static_cast<float>(level.width) / 2.f;
        const auto translatedY = static_cast<float>(tile.y) - static_cast<float>(level.height) / 2.f;

        // Translate the square to its top left corner.
        const auto topLeftCornerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f));

        const auto tileHeight  = static_cast<float>(tile.height);

        // Then translate it to its real position.
        const auto modelMatrix = glm::translate(topLeftCornerMatrix, glm::vec3(translatedX, tileHeight, translatedY));

        game::rendering::setForcedVertexColorShader(mesh.bindShader(), tile.color);

        mesh.draw(projectionViewMatrix, modelMatrix);
    }

    void
    renderFloor(
        game::ecs::Scene&               scene,
        const std::chrono::milliseconds
    ) {
        const auto cameraState          = computeFirstCameraState(scene);
        const auto levelComponent       = scene.getFirstComponent<game::levels::LevelComponent>();

        const auto unitSquareMesh       = game::rendering::findMeshInFirstRenderingAssetsVault(scene, UnitSquare::meshName);

        if (!cameraState.has_value() || !unitSquareMesh.has_value() || !levelComponent.has_value()) {
            return;
        }

        const auto projectionViewMatrix = cameraState.value().getProjectionViewMatrix();

        for (const auto& [entity, tile]: scene.findEntitiesWithComponent<game::levels::Tile>()) {
            renderFloorTile(**levelComponent, *tile, projectionViewMatrix, *unitSquareMesh);
        }
    }
}
