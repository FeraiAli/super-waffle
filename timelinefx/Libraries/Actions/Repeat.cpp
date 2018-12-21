#include "Repeat.h"

namespace Core
{

Repeat::Repeat(const ActionFn& action, size_t repeatLimit)
    : m_action(action)
    , m_mutableAction(action)
    , m_repeatLimit(repeatLimit)
    , m_repeatCount(0)
{}

Repeat::Repeat(Repeat &&other)
    : m_action(std::move(other.m_action))
    , m_mutableAction(m_action)
    , m_repeatLimit(std::move(other.m_repeatLimit))
    , m_repeatCount(0)
{}

Repeat::Repeat(const Repeat &other)
    : m_action(other.m_action)
    , m_mutableAction(m_action)
    , m_repeatLimit(other.m_repeatLimit)
    , m_repeatCount(0)
{}

Repeat& Repeat::operator=(Repeat &&other)
{
    m_action = std::move(other.m_action);
    m_mutableAction = m_action;
    m_repeatLimit = std::move(other.m_repeatLimit);
    m_repeatCount = 0;
    return *this;
}

Repeat& Repeat::operator=(const Repeat &other)
{
    m_action = other.m_action;
    m_mutableAction = m_action;
    m_repeatLimit = other.m_repeatLimit;
    m_repeatCount = 0;
    return *this;
}

Status Repeat::operator()()
{
    auto actionStatus = m_mutableAction();
    if(Status::Running == actionStatus)
    {
        return Status::Running;
    }

    if(Infinity == m_repeatLimit)
    {
        m_mutableAction = m_action;
        return Status::Running;
    }

    m_repeatCount++;
    if(m_repeatCount == m_repeatLimit)
    {
        return Status::Finished;
    }

    m_mutableAction = m_action;
    return Status::Running;
}


} //end of Core
