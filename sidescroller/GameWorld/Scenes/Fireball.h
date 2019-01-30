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
    void Start(const sf::Vector2f& pos);
    void Update(const sf::RectangleShape& shape);
    void Draw(sf::RenderWindow& window);
    bool IsAlive() const;
private:
    void setDirection(const sf::Vector2f& pos);
    void outOfBounds();
    bool interaction(const sf::RectangleShape& shape);
private:
    sf::Sprite m_sprite;
    sf::RectangleShape m_ballRect;

    bool m_alive = false;
    float m_speed = 5.0f;
    sf::Vector2f m_velocity;
    sf::Vector2f m_startingPos = {1100, 730};
    std::map<std::string, Animation> m_animation;
    std::map<std::string, Animation>::iterator iter = m_animation.end();
};
