#pragma once
#include <SFML/System/Vector2.hpp>

namespace Core
{

template<typename T>
sf::Vector2<T> operator*(float t, const sf::Vector2<T>& other)
{
    return {t * other.x,
            t * other.y};
}

}
