#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "AgentTag.h"
#include <memory>
#include <chrono>

struct Agent
{
    using Ptr = std::shared_ptr<Agent>;

    Agent();
    void AddTag(AgentTag tag);
    void RemoveTag(AgentTag tag);
    bool HasTag(AgentTag tag);
    bool HasTag(size_t tag);

    sf::Vector2f velocity;
    sf::Vector2f accelaration;
    sf::RectangleShape shape;

    bool isJumping = false;
    bool isGrounded = false;
    std::chrono::milliseconds jumpTime = std::chrono::milliseconds(385);
    std::chrono::milliseconds jumpTimeCounter = std::chrono::milliseconds::zero();
private:
    size_t m_tags = 0;
};
