#pragma once
#include "Agent/Agent.h"
#include "Agent/AgentTag.h"
#include <memory>
#include <vector>

class BaseAgentSystem
{
public:
    virtual ~BaseAgentSystem() = default;
    using uPtr = std::unique_ptr<BaseAgentSystem>;

    virtual size_t Requires() = 0;
    virtual void Process(std::vector<Agent::Ptr> agents) = 0;
};
