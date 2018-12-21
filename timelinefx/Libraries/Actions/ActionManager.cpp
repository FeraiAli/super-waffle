#include "ActionManager.h"

namespace Core
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
    auto status = m_mutableAction();
    if(status == Status::Finished)
    {
        m_running = false;
    }
}

} //end of Core
