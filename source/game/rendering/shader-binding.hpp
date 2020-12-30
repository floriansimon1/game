#pragma once

#include <game/base/non-copyable.hpp>

#include <SFML/Graphics/Shader.hpp>

namespace game::rendering {
    // Note that this class offers no guarantee that nobody will bind another shader while this one is supposed to be bound.
    class ShaderBinding: private game::base::NonCopyable {
        private:
            bool moved = false;

        public:
            ShaderBinding(
                sf::Shader& shader
            );

            ShaderBinding(
                ShaderBinding&& shader
            );

            ~ShaderBinding();

            sf::Shader& shader;
    };
}
