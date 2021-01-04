#pragma once

#include <game/data/paths.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <memory>

namespace game::data {
    class Textures {
        public:
            static inline const char* grassTextureName = "grass";

            static std::unique_ptr<sf::Texture>
            getGrassTexture();
    };
}
