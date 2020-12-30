find_package(glm      MODULE REQUIRED)
find_package(coro     MODULE REQUIRED)
find_package(range-v3 MODULE REQUIRED)

add_library(ecs OBJECT
    component.hpp
    system.hpp

    scene.hpp
    scene.cpp

    entity.hpp
    entity.cpp

    transform.hpp
    transform.cpp

    spin.hpp
    spin.cpp
)

target_link_libraries(ecs
    PUBLIC
        glm::glm
        coro::coro
        range-v3::range-v3
)

add_library(game::ecs ALIAS ecs)
