add_library(base OBJECT
    non-copyable.hpp
)

add_library(game::base ALIAS base)
