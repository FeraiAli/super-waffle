#include "CollisionSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/Components.h"

#include <iostream>

void CollisionSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();

    auto tiles = pool.GetEntities<Tile>();
    auto agents = pool.GetEntities<Agent>();

    for(const auto& tile : tiles)
    {
        const auto& tileBody = tile->GetComponent<Body>();
        sf::FloatRect tileBox = {tileBody.getPosition().x, tileBody.getPosition().y,
                                 tileBody.size.x, tileBody.size.y};

        for(auto& agent : agents)
        {
            auto& agentBody = agent->GetComponent<Body>();
            agentBody.isGrounded = false;

            sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
                                      agentBody.size.x, agentBody.size.y};

            sf::FloatRect intersectArea;
            if(tileBox.intersects(agentBox, intersectArea))
            {
                agentBody.setPosition(0.0f, -intersectArea.height);
                std::cout << "Move: " << intersectArea.height << std::endl;
            }
//            const auto tileTopPosition = tile->GetComponent<Body>().getPosition().y;
//            const auto agentBottomPoint = agentBody.getPosition().y + agentBody.size.y;

//            if(tileBox.contains(agentBody.getPosition().x, agentBottomPoint))
//            {
//                agentBody.setPosition(agentBody.getPosition().x, tileTopPosition - agentBody.size.y);
//                agentBody.velocity.y = 0.0f;
//            }

//            //Forgiving Jump
//            if(tileBox.contains(agentBody.getPosition().x - 15, agentBottomPoint + 5) ||
//               tileBox.contains(agentBody.getPosition().x + 15, agentBottomPoint + 5))
//            {
//                agentBody.isGrounded = true;
//            }
        }
    }
}

