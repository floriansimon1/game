add_library(data OBJECT
    paths.cpp
    paths.hpp
)

include(../../../cmake/locations.cmake)

target_set_runtime_shader_location_define(data)

add_library(game::data ALIAS data)
