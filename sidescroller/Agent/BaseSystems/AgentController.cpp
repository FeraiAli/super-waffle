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
    for (auto& agent : agents)
    {
        if(agent->isJumping)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                agent->jumpTimeCounter += 15ms;
                if(agent->jumpTimeCounter >= agent->jumpTime)
                {
                    agent->isJumping = false;
                }
                else
                {
                    agent->velocity.y = Math::RangeMap(agent->jumpTimeCounter.count(), int64_t(0),
                                                       agent->jumpTime.count(), -22.0f, 0.0f,
                                                       Math::Easing::inQuint);
                }
            }
            else
            {
                agent->velocity.y = 0.0f;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(agent->isGrounded)
            {
                agent->isJumping = true;
                agent->isGrounded = false;
                agent->velocity.y -= 22.0f; //JUMP SPEED
                agent->jumpTimeCounter = std::chrono::milliseconds::zero();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  agent->accelaration.x -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) agent->accelaration.x += 5;

        agent->velocity += agent->accelaration;
        agent->shape.move(agent->velocity);


        agent->accelaration = {};
        agent->velocity = {};
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
    for (auto& agent : agents)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) agent->accelaration.y -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) agent->accelaration.y += 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) agent->accelaration.x -= 5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) agent->accelaration.x += 5;

        agent->velocity += agent->accelaration;
        agent->shape.move(agent->velocity);

        agent->accelaration = {};
        agent->velocity = {};
    }
}
