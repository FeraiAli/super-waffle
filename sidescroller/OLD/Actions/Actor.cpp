#include "Actor.h"
#include <algorithm>
#include <iostream>

void Actor::Details::ActionUpdater::RunAction(Action::ActionFn &&action)
{
    Action::ActionManager actionManager;
    actionManager.SetAction(std::move(action));
    actionManager.Start();
    m_actions.emplace_back(std::move(actionManager));
}

void Actor::Details::ActionUpdater::Update()
{
    auto iter = std::remove_if(m_actions.begin(), m_actions.end(),
    [](Action::ActionManager& action)
    {
        action.Update();
        return action.IsFinished();
    });
    m_actions.erase(iter, m_actions.end());
}

Actor::Details::ActionUpdater &Actor::Details::GetActionUpdater()
{
    static ActionUpdater actionUpdater;
    return actionUpdater;
}

void Actor::Run(Action::ActionFn&& action)
{
    Actor::Details::GetActionUpdater().RunAction(std::move(action));
}


