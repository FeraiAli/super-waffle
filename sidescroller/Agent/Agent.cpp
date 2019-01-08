#include "Agent.h"

Agent::Agent()
{
    shape.setPosition(700, 20);
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    shape.setSize({25, 50});
}

void Agent::AddTag(AgentTag tag)
{
    m_tags |= static_cast<size_t>(tag);
}

void Agent::RemoveTag(AgentTag tag)
{
    m_tags &= ~(1 << static_cast<size_t>(tag));
}

bool Agent::HasTag(AgentTag tag)
{
    return m_tags & static_cast<size_t>(tag);
}

bool Agent::HasTag(size_t tag)
{
    return m_tags & tag;
}
