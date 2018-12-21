#include "Delay.h"

namespace Core
{

Delay::Delay(Delay::Milli delay)
    : m_delay(delay)
    , m_elapsed(Milli::zero())
{}

Delay::Delay(Delay &&other)
    : m_delay(std::move(other.m_delay))
    , m_elapsed(Milli::zero())
{}

Delay::Delay(const Delay &other)
    : m_delay(other.m_delay)
    , m_elapsed(Milli::zero())
{}

Delay& Delay::operator=(Delay &&other)
{
    m_delay = std::move(other.m_delay);
    m_elapsed = Milli::zero();
    return *this;
}

Delay& Delay::operator=(const Delay &other)
{
    m_delay = other.m_delay;
    m_elapsed = Milli::zero();
    return *this;
}

Status Delay::operator()()
{
    m_elapsed += Milli(15);
    if(m_elapsed >= m_delay)
    {
        return Status::Finished;
    }
    return Status::Running;
}

} //end of Core
