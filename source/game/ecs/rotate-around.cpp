#include <game/ecs/rotate-around.hpp>

#include <game/math/constants.hpp>

#include <game/ecs/scene.hpp>
#include <game/ecs/transform.hpp>

#include <glm/gtx/matrix_interpolation.hpp>

#include <cmath>

namespace game::ecs {
    RotateAround::RotateAround(
        const float       speed,
        const float       height,
        const glm::vec3   center,
        const float       circleAmplitude
    )
    : speed(speed)
    , height(height)
    , center(center)
    , currentAngle(0.f)
    , circleAmplitude(circleAmplitude)
    {}

    game::math::CardinalDirection
    RotateAround::getCardinalDirection() const {
        return game::math::trigonometricAngleToCardinalDirection(this->currentAngle);
    }

    void
    rotateAround(
        Scene&                          scene,
        const std::chrono::milliseconds Δt
    ) {
        for (const auto [entity, transformComponent, rotateAroundComponent]: scene.findEntitiesWithComponents<Transform, RotateAround>()) {
            const auto Δangle = rotateAroundComponent->speed * game::math::completePeriod * (static_cast<float>(Δt.count()) / 1000.f);

            rotateAroundComponent->currentAngle = fmod(rotateAroundComponent->currentAngle + Δangle, game::math::completePeriod);

            transformComponent->position = rotateAroundComponent->circleAmplitude * glm::vec3(
                cos(rotateAroundComponent->currentAngle),
                0.f,
                -sin(rotateAroundComponent->currentAngle)
            );

            transformComponent->position.y  = rotateAroundComponent->height;

            const auto lookDownRayLength    = hypotf(rotateAroundComponent->circleAmplitude, rotateAroundComponent->height);
            const auto directionVector      = rotateAroundComponent->center - transformComponent->position;

            const auto lookDownAxis         = glm::cross(directionVector, glm::vec3(0, -1.f, 0.f));
            const auto lookDownAngle        = acosf(rotateAroundComponent->circleAmplitude / lookDownRayLength);

            transformComponent->orientation = glm::axisAngleMatrix(lookDownAxis, lookDownAngle) * glm::eulerAngleY(rotateAroundComponent->currentAngle + game::math::quarterPeriod);
        }
    }
}
