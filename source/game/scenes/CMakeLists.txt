find_package(sfml     MODULE REQUIRED)
find_package(range-v3 MODULE REQUIRED)

add_library(scenes OBJECT
    battlefield-scene.hpp
    battlefield-scene.cpp
)

target_link_libraries(scenes
    PRIVATE
        sfml::sfml

        game::ecs
        game::rendering
)

add_library(game::scenes ALIAS scenes)
