add_library(levels OBJECT
    relief-generator.hpp
    relief-generator.cpp

    sections-generator.hpp
    sections-generator.cpp

    level-generator.hpp
    level-generator.cpp

    level-section.hpp
    level-section.cpp

    tile.cpp
    tile.hpp

    level.hpp
    level.cpp
)

add_library(game::levels ALIAS levels)

target_link_libraries(levels
    PRIVATE
        game::math)
