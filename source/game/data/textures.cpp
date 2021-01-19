#include <game/data/textures.hpp>

namespace game::data {
    std::unique_ptr<sf::Texture>
    Textures::getGrassTexture() {
        auto texture = std::make_unique<sf::Texture>();

        texture->loadFromFile(Paths::texturesRoot + "grass.png");

        return texture;
    }

    std::unique_ptr<sf::Texture>
    Textures::getDirtTexture() {
        auto texture = std::make_unique<sf::Texture>();

        texture->loadFromFile(Paths::texturesRoot + "dirt.png");

        texture->setRepeated(true);

        return texture;
    }
}
