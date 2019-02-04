#pragma once
#include "ZombieAnimationState.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Fireball.h"
#include "HealthBar.h"

class Zombie : public sf::Sprite
{
public:
    void Init(sf::Vector2f pos);
    void Update(const sf::RectangleShape& shape);
    void Draw(sf::RenderWindow& window);
    void AttackChar(bool attack);
    void CheckForEnemy();
    HealthBar& GetHealthBar();

    sf::RectangleShape bodyRect;
    sf::RectangleShape m_zombieMelee;
private:
    void isAlive();
    void rangeAttack(const sf::RectangleShape& shape);
    void removeFireballs();
private:
    bool m_attackChar = true;
    HealthBar m_healthBar;
    ZombieAnimationState m_animState;

    std::vector<Fireball> m_fireballAnimations;
    std::chrono::milliseconds elapsed = std::chrono::milliseconds::zero();
    std::chrono::milliseconds nextFireball = std::chrono::milliseconds(850);
};
