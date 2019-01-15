#pragma once
#include "ActionDescription.h"
#include <vector>

namespace Action
{

//TODO - addActionFn() and default constructable
class Sequence
{
public:
    explicit Sequence(std::initializer_list<ActionFn>&& actions);

    Sequence(Sequence&& other);
    Sequence(const Sequence& other);

    Sequence& operator=(Sequence&& other);
    Sequence& operator=(const Sequence& other);

    Status operator()();
private:
    std::vector<ActionFn> m_actions;
    std::vector<ActionFn>::iterator m_activeAction = m_actions.end();
};

} //end of namespace
