include(../../../cmake/locations.cmake)

find_package(glad MODULE REQUIRED)

define_global_output_directory()

add_library(rendering OBJECT
    render-level.cpp
    render-level.hpp
)

target_link_libraries(rendering
    PRIVATE
        glad::glad
)

add_library(game::rendering ALIAS rendering)

install(FILES vertex.vert   DESTINATION "${OUTPUT_ROOT_DIRECTORY}/shaders")
install(FILES fragment.frag DESTINATION "${OUTPUT_ROOT_DIRECTORY}/shaders")
