#pragma once
#include "ZombieAnimationState.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Zombie : public sf::Sprite
{
public:
    void Init();
    void Update();
    void Draw(sf::RenderWindow& window);
    void AttackChar(bool attack);
    void CheckForEnemy();

//    const sf::FloatRect GetRangeBounds() const;

    sf::RectangleShape m_zombieMelee;
//    sf::RectangleShape m_zombieRange;
private:
    ZombieAnimationState m_animState;
};
