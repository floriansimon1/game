#include <game/scenes/battlefield-scene.hpp>

#include <glad/glad.h>

#include <SFML/Window.hpp>

#include <chrono>
#include <thread>

int
main(
    int,
    char**
) {
    const float width  = 800.f;
    const float height = 600.f;
    bool        stop   = false;

    auto        window = sf::Window(sf::VideoMode(width, height), "My window");

    if (!gladLoadGL()) {
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.52f, 0.81f, 0.92f, 1.0f);

    game::ecs::Scene battlefieldScene = game::scenes::makeBattlefieldScene(width / height);

    auto lastRenderedFrameTime = std::chrono::system_clock::now();

    while (!stop) {
        sf::Event   event;
        const auto  currentFrameTime = std::chrono::system_clock::now();

        const auto  Δt               = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - lastRenderedFrameTime);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop = true;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        battlefieldScene.process(Δt);

        window.display();

        lastRenderedFrameTime = currentFrameTime;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000u / 144u) - Δt);
    }

    return EXIT_SUCCESS;
}
