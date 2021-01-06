#include <game/rendering/render-floor.hpp>

#include <game/rendering/shaders/standard-textured-surface.hpp>

#include <game/rendering/rendering-assets-vault.hpp>
#include <game/rendering/unit-square.hpp>
#include <game/rendering/camera.hpp>

#include <game/data/textures.hpp>

#include <game/levels/tile.hpp>
#include <game/levels/level.hpp>

#include <game/ecs/scene.hpp>

#include <glm/gtx/euler_angles.hpp>

// TODO DEBUG
#include <game/math/direction.hpp>
#include <iostream>

namespace game::rendering {
    // Matrix calculations in here are easily memoized.
    static void
    renderFloorTile(
        const game::levels::LevelComponent& level,
        const game::levels::Tile&           tile,
        const glm::mat4&                    projectionViewMatrix,
        Mesh&                               mesh,
        const sf::Texture&                  grassTexture
    ) {
        const auto translatedX = static_cast<float>(tile.x) - static_cast<float>(level.width) / 2.f;
        const auto translatedY = static_cast<float>(tile.y) - static_cast<float>(level.height) / 2.f;

        // Translate the square to its top left corner.
        const auto topLeftCornerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f));

        const auto tileHeight  = static_cast<float>(tile.height);

        // Then translate it to its real position.
        const auto modelMatrix = glm::translate(topLeftCornerMatrix, glm::vec3(translatedX, tileHeight, translatedY));

        game::rendering::setTextureForStandardTexturedShader(mesh.bindShader(), grassTexture);

        mesh.draw(projectionViewMatrix, modelMatrix);
    }

    void
    renderFloor(
        game::ecs::Scene&               scene,
        const std::chrono::milliseconds
    ) {
        const auto cameraState    = computeFirstCameraState(scene);
        const auto assetsVault    = scene.getFirstComponent<RenderingAssetsVault>();
        const auto levelComponent = scene.getFirstComponent<game::levels::LevelComponent>();

        if (!cameraState.has_value() || !assetsVault.has_value() || !levelComponent.has_value()) {
            return;
        }

        const auto unitSquareMeshIterator = assetsVault.value()->meshes.find(UnitSquare::meshName);
        const auto grassTextureIterator   = assetsVault.value()->textures.find(game::data::Textures::grassTextureName);

        if (unitSquareMeshIterator == assetsVault.value()->meshes.end() || grassTextureIterator == assetsVault.value()->textures.end()) {
            return;
        }

        const auto projectionViewMatrix = cameraState.value().getProjectionViewMatrix();

        std::cout << glm::degrees(cameraState.value().rotateAround.currentAngle) << ": " << game::math::cardinalDirectionToString(cameraState.value().rotateAround.getCardinalDirection()) << std::endl;

        for (const auto& [entity, tile]: scene.findEntitiesWithComponent<game::levels::Tile>()) {
            renderFloorTile(**levelComponent, *tile, projectionViewMatrix, unitSquareMeshIterator->second, grassTextureIterator->second);
        }
    }
}
