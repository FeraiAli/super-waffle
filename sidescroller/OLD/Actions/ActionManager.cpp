#include "ActionManager.h"

namespace Action
{

void ActionManager::SetAction(ActionFn &&action)
{
    m_action = std::move(action);
    m_mutableAction = m_action;
}

void ActionManager::Start()
{
    m_running = true;
    m_mutableAction = m_action;
}

void ActionManager::Stop()
{
    m_running = false;
}

void ActionManager::Update()
{
    if(nullptr == m_mutableAction)
    {
        m_running = false;
    }
    else
    {
        auto status = m_mutableAction();
        if(status == Status::Finished)
        {
            m_running = false;
        }
    }
}

bool ActionManager::IsFinished() const
{
    return (false == m_running);
}

} //end of namespace
