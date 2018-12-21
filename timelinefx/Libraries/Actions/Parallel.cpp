#include "Parallel.h"

namespace Core
{

Parallel::Parallel(std::initializer_list<ActionFn> &&actions)
    : m_actions{std::move(actions)}
{}

Parallel::Parallel(Parallel&& other)
    : m_actions(std::move(other.m_actions))
{}

Parallel::Parallel(const Parallel &other)
    : m_actions(other.m_actions)
{}

Parallel& Parallel::operator=(Parallel &&other)
{
    m_actions = std::move(other.m_actions);
    return *this;
}

Parallel& Parallel::operator=(const Parallel &other)
{
    m_actions = other.m_actions;
    return *this;
}

Status Parallel::operator()()
{
    Status generalStatus = Status::Finished;
    for(auto& action : m_actions)
    {
        auto actionStatus = action();
        if(Status::Running == actionStatus)
        {
            generalStatus = Status::Running;
        }
    }
    return generalStatus;
}

} //end of Core
