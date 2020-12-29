#include <game/data/paths.hpp>

// This is just to avoid squigglies.
#ifndef SHADERS_RELATIVE_DIRECTORY_MACRO
    #define SHADERS_RELATIVE_DIRECTORY_MACRO ""
#endif

namespace game::data {
    const std::string Paths::shadersRoot = SHADERS_RELATIVE_DIRECTORY_MACRO;
}
