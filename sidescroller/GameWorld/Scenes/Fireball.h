#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Animation.h"
#include <iterator>
#include <map>

class Fireball
{
public:
    void Start(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
    void Update(const sf::RectangleShape& shape);
    void Draw(sf::RenderWindow& window);
    bool IsAlive() const;
    bool interaction(const sf::RectangleShape& shape);
private:
    void setDirection(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
    void outOfBounds();
private:
    sf::Sprite m_sprite;
    sf::RectangleShape m_ballRect;

    bool m_alive = false;
    float m_speed = 5.0f;
    sf::Vector2f m_velocity;
    std::map<std::string, Animation> m_animation;
    std::map<std::string, Animation>::iterator iter = m_animation.end();
};
