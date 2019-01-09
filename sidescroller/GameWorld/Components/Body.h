#pragma once
#include <SFML/Graphics/Transformable.hpp>

struct Body : public sf::Transformable
{
    sf::Vector2f velocity;
    sf::Vector2f size;
    bool isGrounded = false;
};
