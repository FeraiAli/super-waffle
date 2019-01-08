#pragma once
#include "BaseAgentSystem.h"

class AgentArrowController : public BaseAgentSystem
{
public:
private:
    size_t Requires() final override;
    void Process(std::vector<Agent::Ptr> agents) final override;
};

class AgentWASDController : public BaseAgentSystem
{
public:
private:
    size_t Requires() final override;
    void Process(std::vector<Agent::Ptr> agents) final override;
};
