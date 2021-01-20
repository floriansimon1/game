#include <game/scenes/battlefield-scene.hpp>

#include <glad/glad.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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

    sf::ContextSettings windowSettings(24);

    auto window = sf::RenderWindow(sf::VideoMode(width, height), "My window", sf::Style::Resize | sf::Style::Close, windowSettings);

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

        std::this_thread::sleep_for(std::max(std::chrono::milliseconds(0u), std::chrono::milliseconds(1000u / 1440u) - Δt));
    }

    return EXIT_SUCCESS;
}
