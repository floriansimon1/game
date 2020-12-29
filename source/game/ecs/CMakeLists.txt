find_package(glm MODULE REQUIRED)
find_package(coro MODULE REQUIRED)

add_library(ecs OBJECT
    component.hpp
    transform.hpp
    entity.hpp
    system.hpp
    scene.hpp
)

target_link_libraries(ecs
    PUBLIC
        glm::glm
        coro::coro
)

add_library(game::ecs ALIAS ecs)
