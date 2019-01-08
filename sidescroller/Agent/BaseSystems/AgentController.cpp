#include "AgentController.h"
#include "SFML/Window/Event.hpp"
#include <GameFramework/Math/RangeMap.hpp>

using namespace std::chrono_literals;

size_t AgentArrowController::Requires()
{
    return static_cast<size_t>(AgentTag::ArrowsControl);
}

void AgentArrowController::Process(std::vector<Agent::Ptr> agents)
{
    const float AirFriction = 1.15f;
    const float JumpSpeed = 6.5f;
    const float MaxSpeed = 7.0f;
    const float MaxFallingSpeed = 16.0f;
    const float Gravity = 0.3f;
    const std::chrono::milliseconds JumpTime = 235ms;

    for(auto& agent : agents)
    {
        if((agent->velocity.y < 0.0f) and
           (agent->velocity.y > (-4)) and
           (std::abs(agent->velocity.x) > 0.125f))
        {
            agent->velocity.x *= 0.94875f;
        }

        if(agent->isGrounded)
        {
            agent->velocity.x = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) agent->velocity.x = -MaxSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) agent->velocity.x = MaxSpeed;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                agent->jumpTimeCounter = 0ms;
                agent->isJumping = true;
                agent->velocity.y -= JumpSpeed;
            }
        }
        else if(agent->isJumping)
        {
            agent->jumpTimeCounter += 15ms;

            if((agent->jumpTimeCounter >= JumpTime) or
               (false == sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
            {
                agent->isJumping = false;
                agent->velocity.y = std::max(agent->velocity.y, -4.0f);
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) agent->velocity.x -= AirFriction;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) agent->velocity.x += AirFriction;
            agent->velocity.y += Gravity;
        }

        agent->velocity.x = std::min(agent->velocity.x, MaxSpeed);
        agent->velocity.x = std::max(agent->velocity.x, -MaxSpeed);

        agent->velocity.y = std::min(agent->velocity.y, MaxFallingSpeed);
        agent->shape.move(agent->velocity);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

size_t AgentWASDController::Requires()
{
    return static_cast<size_t>(AgentTag::WASDControl);
}

void AgentWASDController::Process(std::vector<Agent::Ptr> agents)
{
    const float AirSpeed = 8.0f;
    const float JumpSpeed = 6.5f;
    const float MaxSpeed = 7.0f;
    const float MaxFallingSpeed = 16.0f;
    const float Gravity = 0.5f;
    const std::chrono::milliseconds JumpTime = 135ms;
    const std::chrono::milliseconds AfterFallingJumpDelay = 60ms;

    for(auto& agent : agents)
    {
        if((agent->velocity.y < 0.0f) and
           (agent->velocity.y > (-4)) and
           (std::abs(agent->velocity.x) > 0.125f))
        {
            agent->velocity.x *= 0.94875f;
        }

        if(agent->isGrounded)
        {
            agent->velocity.x = 0.0f;
            agent->afterFallJumpCounter += 15ms;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) agent->velocity.x = -MaxSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) agent->velocity.x = MaxSpeed;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and
                agent->afterFallJumpCounter >= AfterFallingJumpDelay)
            {
                agent->jumpTimeCounter = 0ms;
                agent->isJumping = true;
                agent->velocity.y -= JumpSpeed;
            }
        }
        else if(agent->isJumping)
        {
            agent->jumpTimeCounter += 15ms;
            agent->afterFallJumpCounter = 0ms;

            if((agent->jumpTimeCounter >= JumpTime) or
               (false == sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
            {
                agent->isJumping = false;
                agent->velocity.y = std::max(agent->velocity.y, -4.0f);
            }
        }
        else
        {
            agent->velocity.x = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) agent->velocity.x = -AirSpeed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) agent->velocity.x = AirSpeed;
            agent->velocity.y += Gravity;
        }

        agent->velocity.x = std::min(agent->velocity.x, MaxSpeed);
        agent->velocity.x = std::max(agent->velocity.x, -MaxSpeed);

        agent->velocity.y = std::min(agent->velocity.y, MaxFallingSpeed);
        agent->shape.move(agent->velocity);
    }




//    for (auto& agent : agents)
//    {
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) agent->accelaration.y -= 5;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) agent->accelaration.y += 5;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) agent->accelaration.x -= 5;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) agent->accelaration.x += 5;

//        agent->velocity += agent->accelaration;
//        agent->shape.move(agent->velocity);

//        agent->accelaration = {};
//        agent->velocity = {};
//    }
}
