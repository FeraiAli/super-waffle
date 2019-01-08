#pragma once
#include "BaseAgentSystem.h"

class TileMap;
class GravitySystem : public BaseAgentSystem
{
public:
    void SetTileMap(TileMap* tileMap);
    size_t Requires() final override;
    void Process(std::vector<Agent::Ptr> agents) final override;
private:
    TileMap* m_tileMap = nullptr;
};
