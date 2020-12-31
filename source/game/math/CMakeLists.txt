find_package(sfml MODULE REQUIRED)

add_library(math OBJECT
    dimensions.hpp

    direction.cpp
    direction.hpp

    random.hpp
    random.implementation.hpp

    sequence-generator.hpp
)

add_library(game::math ALIAS math)

target_link_libraries(math
    PRIVATE
        game::base

    PUBLIC
        sfml::sfml
)
