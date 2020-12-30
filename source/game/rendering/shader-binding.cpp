#include <game/rendering/shader-binding.hpp>

namespace game::rendering {
    ShaderBinding::ShaderBinding(
        sf::Shader& shader
    )
    : shader(shader) {
        sf::Shader::bind(&this->shader);
    }

    ShaderBinding::ShaderBinding(
        ShaderBinding&& binding
    )
    : shader(binding.shader) {
        binding.moved = true;
    }

    ShaderBinding::~ShaderBinding() {
        if (!moved) {
            sf::Shader::bind(nullptr);
        }
    }
}
