#pragma once
#include "Sequence.h"
#include "Parallel.h"
#include "Delay.h"
#include "Repeat.h"

namespace Action
{

class ActionManager
{
public:
    void SetAction(ActionFn&& action);
    void Start();
    void Stop();
    void Update();

    bool IsFinished() const;
private:
    bool m_running = false;

    ActionFn m_action;
    ActionFn m_mutableAction;
};

} //end of namespace
