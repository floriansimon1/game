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
#include <glm/gtx/transform.hpp>

#include <game/math/constants.hpp>
#include <game/math/direction.hpp>

namespace game::rendering {
    static float
    translateLevelCoordinates(
        game::math::Dimension dimension,
        game::math::Dimension maximum
    ) {
        return static_cast<float>(dimension) - static_cast<float>(maximum) / 2.f;
    }

    static glm::mat4
    getTopLeftCornerMatrix() {
        // Translates the square to its top left corner.
        return glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f));
    }

    static void
    renderFloorLink(
        game::levels::Level&                       level,
        const game::levels::Tile&                  tile,
        const sf::Texture&                         dirtTexture,
        const game::math::Direction2d              direction,
        const std::optional<game::math::Dimension> incrementedX,
        const std::optional<game::math::Dimension> incrementedY,
        const glm::mat4&                           projectionViewMatrix,
        Mesh&                                      mesh
    ) {
        const bool isEdgeOfMap         = !incrementedX.has_value() || !incrementedY.has_value();
        const auto makeVerticalAxis    = game::math::isXDirection(direction) ? glm::vec3(0.f, 0.f, 1.f) : glm::vec3(1.f, 0.f, 0.f);

        const int  nextTileHeight      = isEdgeOfMap ? -1 : static_cast<int>(level.getWriteableTile(incrementedX.value(), incrementedY.value())->height);

        const auto Δheight             = nextTileHeight - static_cast<int>(tile.height);

        const bool goesUp              = Δheight > 0;

        if (goesUp || Δheight == 0) {
            return;
        }

        const auto actualX             = translateLevelCoordinates(tile.x + (direction == game::math::Direction2d::right ? 1u : 0u), level.width);
        const auto actualY             = translateLevelCoordinates(tile.y + (direction == game::math::Direction2d::down  ? 1u : 0u), level.height);

        const auto reposition          = glm::translate(glm::mat4(1.f), glm::vec3(actualX, tile.height + (Δheight / 2.f), actualY));

        const auto recenter            = glm::translate(glm::mat4(1.0f), glm::vec3(game::math::isYDirection(direction) ? 0.5f : 0.f, 0.f, game::math::isXDirection(direction) ? 0.5f : 0.f));

        const auto reorientFactor      = direction == game::math::Direction2d::up || direction == game::math::Direction2d::right ? -1.f : 1.f;

        const auto scale               = glm::scale(glm::mat4(1.f), glm::vec3(1.f, reorientFactor * (Δheight * -1.f), 1.f));

        const auto makeVertical        = glm::rotate(glm::mat4(1.f), game::math::quarterPeriod, makeVerticalAxis);

        const auto modelMatrix         = reposition * recenter * scale * makeVertical;

        const bool xTextureIsRescaled  = game::math::isXDirection(direction);

        const auto textureXScale       = xTextureIsRescaled ? -1.f * Δheight : 1.f;
        const auto textureYScale       = xTextureIsRescaled ? 1.f            : -1.f * Δheight;

        game::rendering::setTextureForStandardTexturedShader(mesh.bindShader(), dirtTexture, textureXScale, textureYScale);

        mesh.draw(projectionViewMatrix, modelMatrix);
    }

    static void
    renderFloorLinks(
        game::levels::Level&                level,
        const game::levels::Tile&           tile,
        const sf::Texture&                  dirtTexture,
        const glm::mat4&                    projectionViewMatrix,
        Mesh&                               mesh
    ) {
        renderFloorLink(
            level,
            tile,
            dirtTexture,
            game::math::Direction2d::right,
            game::math::incrementBounded2dX(level.width, game::math::Direction2d::right, tile.x),
            tile.y,
            projectionViewMatrix,
            mesh
        );

        renderFloorLink(
            level,
            tile,
            dirtTexture,
            game::math::Direction2d::up,
            tile.x,
            game::math::incrementBounded2dY(level.width, game::math::Direction2d::up, tile.y),
            projectionViewMatrix,
            mesh
        );

        renderFloorLink(
            level,
            tile,
            dirtTexture,
            game::math::Direction2d::left,
            game::math::incrementBounded2dX(level.width, game::math::Direction2d::left, tile.x),
            tile.y,
            projectionViewMatrix,
            mesh
        );

        renderFloorLink(
            level,
            tile,
            dirtTexture,
            game::math::Direction2d::down,
            tile.x,
            game::math::incrementBounded2dY(level.width, game::math::Direction2d::down, tile.y),
            projectionViewMatrix,
            mesh
        );
    }

    // Matrix calculations in here are easily memoized.
    static void
    renderFloorTile(
        game::levels::Level&                level,
        const game::levels::Tile&           tile,
        const glm::mat4&                    projectionViewMatrix,
        Mesh&                               mesh,
        const sf::Texture&                  grassTexture,
        const sf::Texture&                  dirtTexture
    ) {
        // Then translate it to its real position.
        const auto modelMatrix = glm::translate(getTopLeftCornerMatrix(), glm::vec3(
            translateLevelCoordinates(tile.x, level.width),
            tile.height,
            translateLevelCoordinates(tile.y, level.height)
        ));

        game::rendering::setTextureForStandardTexturedShader(mesh.bindShader(), grassTexture, 1.f, 1.f);

        mesh.draw(projectionViewMatrix, modelMatrix);

        renderFloorLinks(level, tile, dirtTexture, projectionViewMatrix, mesh);
    }

    void
    renderFloor(
        game::ecs::Scene&               scene,
        const std::chrono::milliseconds
    ) {
        const auto cameraState = computeFirstCameraState(scene);
        const auto assetsVault = scene.getFirstComponent<RenderingAssetsVault>();
        auto       level       = scene.getFirstComponent<game::levels::Level>();

        if (!cameraState.has_value() || !assetsVault.has_value() || !level.has_value()) {
            return;
        }

        const auto unitSquareMeshIterator = assetsVault.value()->meshes.find(UnitSquare::meshName);
        const auto dirtTextureIterator    = assetsVault.value()->textures.find(game::data::Textures::dirtTextureName);
        const auto grassTextureIterator   = assetsVault.value()->textures.find(game::data::Textures::grassTextureName);

        if (unitSquareMeshIterator == assetsVault.value()->meshes.end() || grassTextureIterator == assetsVault.value()->textures.end()) {
            return;
        }

        const auto projectionViewMatrix = cameraState.value().getProjectionViewMatrix();

        for (const auto& [entity, tile]: scene.findEntitiesWithComponent<game::levels::Tile>()) {
            renderFloorTile(**level, *tile, projectionViewMatrix, unitSquareMeshIterator->second, grassTextureIterator->second, dirtTextureIterator->second);
        }
    }
}
