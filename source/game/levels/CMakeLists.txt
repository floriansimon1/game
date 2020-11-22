add_library(levels OBJECT
    sections-generator.hpp
    sections-generator.cpp

    level-generator.hpp
    level-generator.cpp

    level-section.hpp
    level-section.cpp

    tile.hpp

    level.hpp
    level.cpp
)

add_library(game::levels ALIAS levels)
