#pragma once
#include "ActionManager.h"
#include <list>

namespace Actor
{
    void Run(Action::ActionFn &&action);

namespace Details
{
    struct ActionUpdater
    {
        void RunAction(Action::ActionFn&& action);
        void Update();
        std::list<Action::ActionManager> m_actions;
    };
    ActionUpdater& GetActionUpdater();
}
}
