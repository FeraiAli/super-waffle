#include "Zombie.h"

void Zombie::Init()
{
    m_animState.Init();
    setScale({0.2f, 0.2f});
    setPosition(1100, 740);

    m_zombieMelee.setPosition(getPosition().x, getPosition().y);
    m_zombieMelee.setOutlineColor(sf::Color::Black);
    m_zombieMelee.setOutlineThickness(1.0f);
    m_zombieMelee.setFillColor(sf::Color(110, 200, 100));
    m_zombieMelee.setOutlineThickness(1.0f);

//    m_zombieRange.setPosition(getPosition().x - 850, getPosition().y);
//    m_zombieRange.setOutlineColor(sf::Color::Red);
//    m_zombieRange.setOutlineThickness(1.0f);
//    m_zombieRange.setFillColor(sf::Color(110, 200, 100));
//    m_zombieRange.setOutlineThickness(1.0f);
}

void Zombie::Update()
{
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setScale(-0.23f, 0.23f);

    m_zombieMelee.setSize({getGlobalBounds().width, getGlobalBounds().height});
    m_zombieMelee.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);

//    m_zombieRange.setSize({getGlobalBounds().width + 850, getGlobalBounds().height});
//    m_zombieRange.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);

    m_animState.Update();
    setTexture(*m_animState.GetTexutre());
}

void Zombie::Draw(sf::RenderWindow &window)
{
//    window.draw(m_zombieMelee);
//    window.draw(m_zombieRange);
    window.draw(*this);
}

void Zombie::AttackChar(bool attack)
{
    m_animState.Attack(attack);
}

//const sf::FloatRect Zombie::GetRangeBounds() const
//{
//    return m_zombieRange.getGlobalBounds();
//}

