#pragma once
#include "ActionDescription.h"

namespace Action
{

class Repeat
{
public:
    static const size_t Infinity = 0;

    explicit Repeat(const ActionFn& action, size_t repeatLimit = Infinity);

    Repeat(Repeat&& other);
    Repeat(const Repeat& other);

    Repeat& operator=(Repeat&& other);
    Repeat& operator=(const Repeat& other);

    Status operator()();
private:
    ActionFn m_action;
    ActionFn m_mutableAction;
    size_t m_repeatLimit = Infinity;
    size_t m_repeatCount = 0;
};

} //end of namespace


