#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class HealthBar
{
public:
    void Init(sf::Vector2f pos);
    void Update(sf::Vector2f pos);
    void ChangeHealth();
    int  GetCurrentHealth();
    void Draw(sf::RenderWindow& window);

private:
    sf::Sprite red;
    sf::Sprite green;
    int m_health = 892;
    int m_currentHealth = 892;
};
