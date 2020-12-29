#include <game/levels/level-generator.hpp>

#include <game/rendering/shaders/forced-vertex-color-fragment-shader.hpp>
#include <game/rendering/floor-tile.hpp>
#include <game/rendering/colors.hpp>

#include <game/ecs/scene.hpp>

#include <game/math/random.hpp>

#include <glad/glad.h>

#include <SFML/Window.hpp>

#include <algorithm>
#include <chrono>
#include <thread>

int
main(
    int,
    char**
) {
    const float                  width           = 800.f;
    const float                  height          = 600.f;
    bool                         stop            = false;
    game::ecs::Scene             scene           = game::ecs::Scene();
    auto                         randomGenerator = game::math::random::ReproducibleDimensionGenerator(std::time(nullptr));

    game::levels::Level          level           = game::levels::generateLevel(32u, 32u, randomGenerator);

    sf::Window window(sf::VideoMode(width, height), "My window");

    if (!gladLoadGL()) {
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.52f, 0.81f, 0.92f, 1.0f);

    const auto maxSectionId = std::max_element(level.tiles.cbegin(), level.tiles.cend(), [] (const auto& a, const auto& b) {
        return a.sectionId < b.sectionId;
    })->sectionId;

    const auto colors         = game::rendering::getDistinctColorsArray(maxSectionId);

    for (auto x = 0u; x < level.width; x++) {
        for (auto y = 0u; y < level.height; y++) {
            // Translate the square to its top left corner.
            const auto topLeftCornerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.5f));

            const auto translatedX = static_cast<float>(x) - static_cast<float>(level.width) / 2.f;
            const auto translatedY = static_cast<float>(y) - static_cast<float>(level.height) / 2.f;
            const auto tileHeight  = static_cast<float>(level.getWriteableTile(x, y).height);

            // Then translate it to its real position.
            const auto worldCoordinatesMatrix = glm::translate(topLeftCornerMatrix, glm::vec3(translatedX, tileHeight, translatedY));

            const auto color = colors[level.getWriteableTile(x, y).sectionId % maxSectionId];

            // scene.renderObjects.push_back(std::make_shared<game::rendering::RenderObject>(
            //     game::rendering::squareVertices,
            //     game::rendering::floorTileVertexIndices,
            //     worldCoordinatesMatrix,
            //     game::rendering::getForcedVertexColorShader(color)
            // ));
        }
    }

    while (!stop) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop = true;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // const auto Δt = scene.update();

        // scene.render();

        window.display();

        // std::this_thread::sleep_for(std::chrono::milliseconds(1000u / 144u) - Δt);
    }

    return EXIT_SUCCESS;
}
