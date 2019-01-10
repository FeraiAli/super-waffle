#include "MoveSystem.h"
#include <SFML/Window/Event.hpp>
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>
#include "../Components/Components.h"
#include <cmath>
using namespace std::chrono_literals;

namespace Settings
{
    const float AirSpeed = 8.0f;
    const float JumpSpeed = 6.5f;
    const float GroundSpeed = 7.0f;
    const float MaxSpeed = 9.0f;
    const float MaxFallingSpeed = 16.0f;
    const float Gravity = 0.5f;
    const std::chrono::milliseconds JumpTime = 135ms;
    const std::chrono::milliseconds AfterFallingJumpDelay = 60ms;
}

namespace
{
    bool isJumpPressed(Entita::Entity::Ptr entity)
    {
        if(entity->HasComponent<WASDController>())
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        }
        else if(entity->HasComponent<ArrowController>())
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        }
        return false;
    };

    void moveBody(Entita::Entity::Ptr entity, Body& body, float speed)
    {
        sf::Keyboard::Key left = sf::Keyboard::Unknown;
        sf::Keyboard::Key right = sf::Keyboard::Unknown;

        if(entity->HasComponent<WASDController>())
        {
            left = sf::Keyboard::A;
            right = sf::Keyboard::D;
            body.velocity.x = 0.0f;
        }
        else if(entity->HasComponent<ArrowController>())
        {
            left = sf::Keyboard::Left;
            right = sf::Keyboard::Right;
            body.velocity.x = 0.0f;
        }

        if(sf::Keyboard::isKeyPressed(left))  body.velocity.x = -speed;
        if(sf::Keyboard::isKeyPressed(right)) body.velocity.x = speed;
    }
}

void MoveSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();
    for(auto& entity : pool.GetEntities<Body, Movable, Collidable>())
    {
        auto& body = entity->GetComponent<Body>();
        speedDecrease(body);

        if(entity->HasComponent<Jumpable>())
        {
            handleJumpAndMovement(entity, body);
        }
        else
        {
            if(entity->GetComponent<Collidable>().IsGrounded())
            {
                handleGroundMovement(entity, body);
            }
            else
            {
                handleAirMovement(entity, body);
            }
        }

        speedConstraints(body);
        body.move(body.velocity);
    }
}

void MoveSystem::speedConstraints(Body &body)
{
    body.velocity.x = std::min(body.velocity.x, Settings::MaxSpeed);
    body.velocity.x = std::max(body.velocity.x, -Settings::MaxSpeed);

    body.velocity.y = std::min(body.velocity.y, Settings::MaxFallingSpeed);
}

void MoveSystem::handleJumpAndMovement(EntityPtr entity, Body &body)
{
    auto& jumpSettings = entity->GetComponent<Jumpable>();
    if(entity->GetComponent<Collidable>().IsGrounded())
    {
        jumpSettings.afterFallJumpCounter += 15ms;

        handleGroundMovement(entity, body);

        if (isJumpPressed(entity) and
            jumpSettings.afterFallJumpCounter >= Settings::AfterFallingJumpDelay)
        {
            jumpSettings.jumpTimeCounter = 0ms;
            jumpSettings.isJumping = true;
            body.velocity.y -= Settings::JumpSpeed;
        }
    }
    else if(jumpSettings.isJumping)
    {
        jumpSettings.jumpTimeCounter += 15ms;
        jumpSettings.afterFallJumpCounter = 0ms;

        if((jumpSettings.jumpTimeCounter >= Settings::JumpTime) or
           (false == isJumpPressed(entity)))
        {
            jumpSettings.isJumping = false;
            body.velocity.y = std::max(body.velocity.y, -4.0f);
        }
    }
    else
    {
        handleAirMovement(entity, body);
    }

}

void MoveSystem::handleAirMovement(EntityPtr entity, Body& body)
{
    body.velocity.y += Settings::Gravity;
    moveBody(entity, body, Settings::AirSpeed);
}

void MoveSystem::handleGroundMovement(EntityPtr entity, Body& body)
{
    moveBody(entity, body, Settings::GroundSpeed);
}

void MoveSystem::speedDecrease(Body &body)
{
    if((body.velocity.y < 0.0f) and
       (body.velocity.y > (-4)) and
       (std::abs(body.velocity.x) > 0.125f))
    {
        body.velocity.x *= 0.94875f;
    }
}


