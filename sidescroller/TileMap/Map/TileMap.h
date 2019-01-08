#pragma once
#include "../BaseTileMap.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include "Agent/AgentPool.h"

class TileMap : public BaseTileMap
{
public:
    void Init() override;
    void Show() override;
    void Process() final override;
private:
    AgentPool m_agentPool;
};

