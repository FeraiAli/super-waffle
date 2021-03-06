#pragma once
#include "ActionDescription.h"
#include <chrono>

namespace Action
{

class Delay
{
public:
    using Milli = std::chrono::milliseconds;

    explicit Delay(Milli delay);

    Delay(Delay&& other);
    Delay(const Delay& other);

    Delay& operator=(Delay&& other);
    Delay& operator=(const Delay& other);

    Status operator()();
private:
    Milli m_delay;
    Milli m_elapsed;
};

} //end of namespace



