#pragma once
#include "BaseAgentSystem.h"
#include <vector>

class AgentDrawer : public BaseAgentSystem
{
public:
    size_t Requires() final override;
    void Process(std::vector<Agent::Ptr> agents) final override;
};
