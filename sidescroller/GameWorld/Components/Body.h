#pragma once
#include <SFML/Graphics/Transformable.hpp>

struct Body : public sf::Transformable
{
    sf::Vector2f velocity;
    sf::Vector2f size = {40, 45};
};
