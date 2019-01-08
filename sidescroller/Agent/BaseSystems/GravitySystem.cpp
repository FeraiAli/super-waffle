#include "GravitySystem.h"
#include "TileMap/Map/TileMap.h"

void GravitySystem::SetTileMap(TileMap *tileMap)
{
    m_tileMap = tileMap;
}

size_t GravitySystem::Requires()
{
    return static_cast<size_t>(AgentTag::Gravity);
}

void GravitySystem::Process(std::vector<Agent::Ptr> agents)
{
    const auto& tiles = m_tileMap->GetTiles();
    for(auto& agent : agents)
    {
        agent->isGrounded = false;
        for(const auto& rowTile : tiles)
        {
            for(const auto& tile : rowTile)
            {
                if(tile.getFillColor() != sf::Color(11, 102, 35))
                {
                    continue;
                }

                auto agentDownPos = agent->shape.getPosition().y + agent->shape.getGlobalBounds().height;
                if(tile.getGlobalBounds().contains(agent->shape.getPosition().x, agentDownPos))
                {
                     agent->shape.setPosition(agent->shape.getPosition().x,
                                              tile.getGlobalBounds().top - agent->shape.getGlobalBounds().height);
                     agent->velocity.y = 0.0f;
                }

                agentDownPos = agent->shape.getPosition().y + agent->shape.getGlobalBounds().height;
                if(tile.getGlobalBounds().contains(agent->shape.getPosition().x, agentDownPos + 10))
                {
                    agent->isGrounded = true;
                }
            }
        }
    }

//    for(auto& rowTile : tiles)
//    {
//        for(auto& tile : rowTile)
//        {
//             if(tile.getFillColor() != sf::Color(11, 102, 35))
//             {
//                 continue;
//             }

//             for(auto& agent : agents)
//             {
//                 auto agentDownPoint = agent->shape.getGlobalBounds().top + agent->shape.getGlobalBounds().height;
//                 auto agentRightPoint = agent->shape.getGlobalBounds().left + agent->shape.getGlobalBounds().width;
//                 auto agentLeftPoint = agent->shape.getGlobalBounds().left;

//                 if( tile.getGlobalBounds().contains(agent->shape.getPosition().x, agentDownPoint) )
//                 {
//                    agent->shape.move(0.0f, -(agentDownPoint - tile.getGlobalBounds().top));
//                 }
//                 if( tile.getGlobalBounds().contains(agentRightPoint, agent->shape.getPosition().y) )
//                 {
//                    agent->shape.move(-(agentRightPoint - tile.getGlobalBounds().left), 0.0f);
//                 }
//                 if( tile.getGlobalBounds().contains(agentLeftPoint, agent->shape.getPosition().y) )
//                 {
//                    agent->shape.move(((tile.getGlobalBounds().left + tile.getGlobalBounds().width) - agentLeftPoint), 0.0f);
//                 }
//             }
//        }
//    }
}
