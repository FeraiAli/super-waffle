#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Zombie.h"

class Slash
{
public:
    void Start(const sf::Vector2f& pos, const float& scale, const float& speed);
    void Update(std::vector<Zombie>& zombies);
    void Draw(sf::RenderWindow& window);
    bool IsAlive() const;
private:
    bool interaction(std::vector<Zombie>& zombies);
    void outOfBounds();
private:
    bool m_alive = false;
    float m_speed = 0.f;
    sf::Sprite m_sprite;
    sf::RectangleShape m_rect;
};
