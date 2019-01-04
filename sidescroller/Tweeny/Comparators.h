#pragma once
#include <SFML/System/Vector2.hpp>

template<typename Scalar, typename T>
sf::Vector2<T> operator*(Scalar t, const sf::Vector2<T>& other)
{
    return {t * other.x, t * other.y};
}
