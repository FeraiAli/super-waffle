#pragma once
#include "ActionDescription.h"
#include <vector>

namespace Action
{

//TODO - addActionFn() and default constructable
class Parallel
{
public:
    explicit Parallel(std::initializer_list<ActionFn>&& actions);

//    Parallel(Parallel&& other);
//    Parallel(const Parallel& other);

//    Parallel& operator=(Parallel&& other);
//    Parallel& operator=(const Parallel& other);

    Status operator()();
private:
    std::vector<ActionFn> m_actions;
};

} //end of namespace

