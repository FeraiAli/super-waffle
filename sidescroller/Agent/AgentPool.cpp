#include "AgentPool.h"
#include "BaseSystems/AgentDrawer.h"
#include "BaseSystems/AgentController.h"
#include "Agent.h"

Agent::Ptr AgentPool::CreateAgent()
{
    auto agent = std::make_shared<Agent>();
    m_agents.push_back(agent);
    return agent;
}

void AgentPool::AddSystem(BaseAgentSystem::uPtr&& system)
{
    m_systems.emplace_back(std::move(system));
}

void AgentPool::Process()
{
    for (auto& system : m_systems)
    {
        auto systemRequires = system->Requires();
        std::vector<Agent::Ptr> agents;
        for (auto agent : m_agents)
        {
            if (agent->HasTag(systemRequires))
            {
                agents.push_back(agent);
            }
        }
        system->Process(agents);
    }
}
