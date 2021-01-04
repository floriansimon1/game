
find_package(sfml MODULE REQUIRED)

add_library(data OBJECT
    paths.cpp
    paths.hpp

    textures.hpp
    textures.cpp
)

target_link_libraries(data
    PUBLIC
        sfml::sfml
)

include(../../../cmake/locations.cmake)

define_global_output_directory()

target_set_runtime_textures_location_define(data)
target_set_runtime_shader_location_define(data)

install(DIRECTORY textures DESTINATION "${OUTPUT_ROOT_DIRECTORY}")

add_library(game::data ALIAS data)
