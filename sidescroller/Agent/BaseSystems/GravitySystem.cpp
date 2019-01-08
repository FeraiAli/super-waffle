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
    static const float gravityFactor = 8.0f;
    const auto& tiles = m_tileMap->GetTiles();
    for(auto& agent : agents)
    {
        agent->shape.move(0.0f, gravityFactor);
        auto agentPos = agent->shape.getPosition();
        auto agentDownPos = agentPos.y + agent->shape.getGlobalBounds().height;

        for(auto& rowTile : tiles)
        {
            for(auto& tile : rowTile)
            {
                if(tile.getFillColor() != sf::Color(11, 102, 35))
                {
                    continue;
                }

                if(tile.getGlobalBounds().contains(agent->shape.getPosition().x, agentDownPos))
                {
                     auto deltaY = agentDownPos - tile.getGlobalBounds().top;
                     agent->shape.move(0.0f, -deltaY + 2);
                     agent->isGrounded = true;
                }
                else
                {
                    //agent->isGrounded = false;
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
