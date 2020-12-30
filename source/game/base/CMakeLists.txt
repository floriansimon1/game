add_library(base OBJECT
    non-copyable.hpp

    parameter-pack-type-unicity.hpp

    iterable-to-optional.cpp
    iterable-to-optional.hpp
)

add_library(game::base ALIAS base)
