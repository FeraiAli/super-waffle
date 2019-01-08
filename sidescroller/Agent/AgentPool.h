#pragma once
#include "Agent.h"
#include "BaseSystems/BaseAgentSystem.h"
#include <vector>

class AgentPool
{
public:
    Agent::Ptr CreateAgent();
    void AddSystem(BaseAgentSystem::uPtr&& system);
    void Process();
private:
    std::vector<Agent::Ptr> m_agents;
    std::vector<BaseAgentSystem::uPtr> m_systems;
};
