#include <game/scenes/battlefield-scene.hpp>

#include <game/math/random.hpp>

#include <game/data/textures.hpp>

#include <game/ecs/transform.hpp>
#include <game/ecs/rotate-around.hpp>

#include <game/rendering/mesh.hpp>
#include <game/rendering/camera.hpp>
#include <game/rendering/unit-square.hpp>
#include <game/rendering/render-floor.hpp>
#include <game/rendering/level-coloration.hpp>
#include <game/rendering/rendering-assets-vault.hpp>
#include <game/rendering/shaders/standard-textured-surface.hpp>

#include <game/levels/level-generator.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <memory>

namespace game::scenes {
    static std::shared_ptr<game::ecs::Entity>
    makeCameraEntity(
        const float aspectRatio
    ) {
        auto height    = 10.f;
        auto amplitude = 40.f;

        auto transform = std::make_shared<game::ecs::Transform>();

        return game::ecs::Entity::make({
            transform,
            std::make_shared<game::ecs::RotateAround>(0.1f, height, glm::vec3(0.f, 0.f, 0.f), amplitude),
            std::make_shared<game::rendering::Camera>(aspectRatio)
        });
    }

    static void
    addTileEntities(
        game::levels::Level&  level,
        game::ecs::Scene&     scene
    ) {
        for (auto x = 0u; x < level.width; x++) {
            for (auto y = 0u; y < level.height; y++) {
                scene.addEntity(game::ecs::Entity::make(level.getWriteableTile(x, y)));
            }
        }
    }

    static std::shared_ptr<game::ecs::Entity>
    loadAssets() {
        auto vault = std::make_shared<game::rendering::RenderingAssetsVault>();

        vault->meshes.insert({
            game::rendering::UnitSquare::meshName,
            
            game::rendering::Mesh(
                game::rendering::UnitSquare::vertices,
                game::rendering::UnitSquare::vertexIndices,
                game::rendering::getStandardTexturedSurfaceShader()
            )
        });

        vault->textures.insert({
            game::data::Textures::grassTextureName,
            *game::data::Textures::getGrassTexture()
        });

        return game::ecs::Entity::make(vault);
    }

    static std::shared_ptr<game::ecs::Entity>
    getLevelEntity(
        const game::levels::Level& level
    ) {
        auto levelComponent = std::make_shared<game::levels::LevelComponent>();
        
        levelComponent->width  = level.width;
        levelComponent->height = level.height;

        return game::ecs::Entity::make(levelComponent);
    }

    game::ecs::Scene
    makeBattlefieldScene(
        const float aspectRatio
    ) {
        game::ecs::Scene scene;

        auto                randomGenerator = game::math::random::ReproducibleDimensionGenerator(std::time(nullptr));
        game::levels::Level level           = game::levels::generateLevel(32u, 32u, randomGenerator);

        game::rendering::colorizeLevel(level);

        scene.addEntity(getLevelEntity(level));
        scene.addEntity(makeCameraEntity(aspectRatio));

        addTileEntities(level, scene);

        scene.addEntity(loadAssets());
        scene.addSystem(game::ecs::rotateAround);

        scene.addSystem(game::rendering::renderFloor);

        return scene;
    }
}
