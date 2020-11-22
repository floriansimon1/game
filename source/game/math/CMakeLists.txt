add_library(math OBJECT
    dimensions.hpp

    random.hpp
    random.implementation.hpp

    sequence-generator.hpp
)

add_library(game::math ALIAS math)

target_link_libraries(math
    PRIVATE
        game::base
)
