#include "TileMap.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include "Agent/BaseSystems/AgentController.h"
#include "Agent/BaseSystems/AgentDrawer.h"
#include "Agent/BaseSystems/GravitySystem.h"

void TileMap::Init()
{
    m_agentPool.AddSystem(std::make_unique<AgentArrowController>());
    m_agentPool.AddSystem(std::make_unique<AgentWASDController>());

    auto gravitySystem = std::make_unique<GravitySystem>();
    gravitySystem->SetTileMap(this);
    m_agentPool.AddSystem(std::move(gravitySystem));

    m_agentPool.AddSystem(std::make_unique<AgentDrawer>());

    auto agent1 = m_agentPool.CreateAgent();
    agent1->AddTag(AgentTag::Drawable);
    agent1->AddTag(AgentTag::ArrowsControl);
    agent1->AddTag(AgentTag::Gravity);

    auto agent2 = m_agentPool.CreateAgent();
    agent2->AddTag(AgentTag::Drawable);
    agent2->AddTag(AgentTag::WASDControl);
    agent2->AddTag(AgentTag::Gravity);
}

void TileMap::Show()
{
    BaseTileMap::importMap();
    for(auto& tileRow : m_tiles)
    {
        for(auto& tile : tileRow)
        {
            tile.setOutlineThickness(0.0f);
        }
    }
}

void TileMap::Process()
{
    auto& window = Context::Get<sf::RenderWindow>();
    for(const auto& tileRow : m_tiles)
    {
        for(const auto& tile : tileRow)
        {
            window.draw(tile);
        }
    }

    m_agentPool.Process();
}
