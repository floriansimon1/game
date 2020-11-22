#include <glad/glad.h>

#include <game/levels/generator.hpp>

#include <game/debug/feature-switches.hpp>

#include <game/data/paths.hpp>

#include <game/math/random.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std::literals::chrono_literals;

int
main(
    int,
    char**
) {
    sf::Shader                   shader;
    sf::Texture                  texture;
    GLuint                       triangleVbo;
    GLuint                       triangleVao;
    game::debug::FeatureSwitches featureSwitches;

    const float                  width           = 800.f;
    const float                  height          = 600.f;
    bool                         stop            = false;
    auto                         randomGenerator = game::math::random::ReproducibleDimensionGenerator(2);

    auto                         levelGenerator  = game::levels::Generator(randomGenerator, featureSwitches);

    game::levels::Level          level           = levelGenerator.generate(32u, 32u);

    constexpr GLfloat vertices[] = {
        // Vertex               Texture
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        +0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
        +0.5f, -0.5f, +0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,

        -0.5f, +0.5f, -0.5f,    0.0f, 1.0f,
        +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
        -0.5f, +0.5f, +0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f, +0.5f,    0.0f, 0.0f,

        +0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        +0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
        +0.5f, -0.5f, +0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, +0.5f, -0.5f,    1.0f, 1.0f,
        +0.5f, +0.5f, -0.5f,    1.0f, 0.0f,
        +0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f, +0.5f,    0.0f, 1.0f,
        +0.5f, -0.5f, +0.5f,    1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f,    1.0f, 0.0f,
        -0.5f, +0.5f, +0.5f,    0.0f, 0.0f
    };

    glm::mat4 projection = glm::perspective(glm::radians(50.0f), width / height, 0.1f, 100.0f);

    constexpr GLuint       positionAttribute     = 0;
    constexpr GLuint       textureAttribute      = 1;
    constexpr unsigned int numbersPerVertex      = 3 + 2;

    constexpr unsigned int verticesCount         = sizeof(vertices) / numbersPerVertex;

    sf::Window window(sf::VideoMode(width, height), "My window");

    texture.loadFromFile(game::data::Paths::assetsRoot + "texture.png");

    if (!gladLoadGL()) {
        return EXIT_FAILURE;
    }

    if (!shader.loadFromFile(
        game::data::Paths::shadersRoot + "vertex.vert",
        game::data::Paths::shadersRoot + "fragment.frag")
    ) {
        std::cout << "Could not load shaders!" << std::endl;

        return EXIT_FAILURE;
    }

    glGenBuffers(1, &triangleVbo);
    glGenVertexArrays(1, &triangleVao);
s
    glBindVertexArray(triangleVao);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(decltype(vertices[0])), reinterpret_cast<void*>(0));
    glVertexAttribPointer(textureAttribute,  2, GL_FLOAT, GL_FALSE, numbersPerVertex * sizeof(decltype(vertices[0])), reinterpret_cast<void*>(3 * sizeof(decltype(vertices[0]))));

    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(textureAttribute);

    glEnable(GL_DEPTH_TEST);

    const glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 3.0f, 3.0f), 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    auto last = std::chrono::system_clock::now();

    constexpr float radiansPerMillisecond =  (2 * M_PI) / 2.0f / 1000.0f;

    float angle            = 0.0f;

    while (!stop) {
        std::this_thread::sleep_for(0.05s);

        const auto current = std::chrono::system_clock::now();

        const auto Δt      = current - last;

        std::cout << angle << std::endl;

        angle += radiansPerMillisecond * std::chrono::duration_cast<std::chrono::milliseconds>(Δt).count();

        glm::mat4 model    = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

        sf::Event event;

        glClearColor(0.52f, 0.81f, 0.92f, 1.0f);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop = true;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sf::Shader::bind(&shader);
        sf::Texture::bind(&texture);

        shader.setUniform("view",       sf::Glsl::Mat4(glm::value_ptr(view)));
        shader.setUniform("model",      sf::Glsl::Mat4(glm::value_ptr(model)));
        shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));

        glBindVertexArray(triangleVao);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / (numbersPerVertex * sizeof(decltype(vertices[0]))));

        window.display();

        last = current;
    }

    return EXIT_SUCCESS;
}
