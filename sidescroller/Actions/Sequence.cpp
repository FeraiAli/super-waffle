#include "Sequence.h"

namespace Action
{

Sequence::Sequence(std::initializer_list<ActionFn> &&actions)
    : m_actions{std::move(actions)}
    , m_activeAction(m_actions.begin())
{}

Sequence::Sequence(Sequence &&other)
    : m_actions(std::move(other.m_actions))
    , m_activeAction(m_actions.begin())
{}

Sequence::Sequence(const Sequence &other)
{
    m_actions = other.m_actions;
    m_activeAction = m_actions.begin();
}

Sequence& Sequence::operator=(const Sequence &other)
{
    m_actions = other.m_actions;
    m_activeAction = m_actions.begin();
    return *this;
}

Sequence& Sequence::operator=(Sequence &&other)
{
    m_actions = std::move(other.m_actions);
    m_activeAction = m_actions.begin();
    return *this;
}

Status Sequence::operator()()
{
    if(m_activeAction == m_actions.end())
    {
        return Status::Finished;
    }

    auto actionStatus = (*m_activeAction)();
    if(actionStatus == Status::Finished)
    {
        std::advance(m_activeAction, 1);
    }
    return Status::Running;
}



} //end of namespace
