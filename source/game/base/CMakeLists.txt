add_library(base OBJECT
    non-copyable.hpp

    iterable-to-optional.hpp
)

add_library(game::base ALIAS base)
