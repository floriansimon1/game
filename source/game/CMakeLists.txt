add_subdirectory(base)
add_subdirectory(data)
add_subdirectory(math)
add_subdirectory(ecs)

add_subdirectory(levels)
add_subdirectory(rendering)

add_subdirectory(scenes)

find_package(sfml MODULE REQUIRED)
find_package(glad MODULE REQUIRED)

add_executable(game
    main.cpp
)

target_link_libraries(game
    PRIVATE
        game::ecs
        game::data
        game::base
        game::math
        game::scenes
        game::levels
        game::rendering

        sfml::sfml
        glad::glad
)

include(../../cmake/locations.cmake)

define_global_output_directory()

install(TARGETS game DESTINATION "${OUTPUT_ROOT_DIRECTORY}")
