include(../../../cmake/locations.cmake)

find_package(glm      MODULE REQUIRED)
find_package(glad     MODULE REQUIRED)
find_package(sfml     MODULE REQUIRED)
find_package(range-v3 MODULE REQUIRED)

define_global_output_directory()

add_library(rendering OBJECT
    camera.hpp
    camera.cpp

    render-floor.cpp
    render-floor.hpp

    render-object.cpp
    render-object.hpp

    floor-tile.hpp

    colors.hpp
    colors.cpp

    shaders/forced-vertex-color-fragment-shader.cpp
    shaders/forced-vertex-color-fragment-shader.hpp
)

target_link_libraries(rendering
    PRIVATE
        glad::glad
        
        game::ecs
        game::math
        game::data

    PUBLIC
        glm::glm
        range-v3::range-v3
)

add_library(game::rendering ALIAS rendering)

install(DIRECTORY shaders/glsl DESTINATION "${OUTPUT_ROOT_DIRECTORY}/shaders")
