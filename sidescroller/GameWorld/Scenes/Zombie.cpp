#include "Zombie.h"
#include <GameFramework/System/Random.h>
using namespace std::chrono_literals;

void Zombie::Init(sf::Vector2f pos)
{
    m_animState.Init();
    setScale({0.2f, 0.2f});
    setPosition(pos);
    m_healthBar.Init({pos.x - 50, pos.y - 80});
    m_fireballAnimations.reserve(64);

    m_zombieMelee.setPosition(getPosition().x, getPosition().y);
    m_zombieMelee.setOutlineColor(sf::Color::Black);
    m_zombieMelee.setOutlineThickness(1.0f);
    m_zombieMelee.setFillColor(sf::Color(110, 200, 100));
    m_zombieMelee.setOutlineThickness(1.0f);

    bodyRect.setSize({60, 90});
    bodyRect.setFillColor(sf::Color::Black);
    sf::FloatRect rect = bodyRect.getGlobalBounds();
    bodyRect.setOrigin(rect.width / 2, rect.height / 2);
    bodyRect.setPosition(getPosition().x, getPosition().y + 10);
}

void Zombie::Update(const sf::RectangleShape& shape)
{
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
    setScale(-0.23f, 0.23f);

    for (auto& ball : m_fireballAnimations) { ball.Update(shape); }
    rangeAttack(shape);
    removeFireballs();

    m_zombieMelee.setSize({getGlobalBounds().width, getGlobalBounds().height});
    m_zombieMelee.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);

    isAlive();
    m_animState.Update();
    setTexture(*m_animState.GetTexutre());
}

void Zombie::Draw(sf::RenderWindow &window)
{
//    window.draw(m_zombieMelee);
    window.draw(*this);
    m_healthBar.Draw(window);
    for (auto& ball : m_fireballAnimations) { ball.Draw(window); }
}

void Zombie::AttackChar(bool attack)
{
    m_animState.Attack(attack);
}

HealthBar &Zombie::GetHealthBar()
{
    return m_healthBar;
}

void Zombie::isAlive()
{
    if (m_healthBar.GetCurrentHealth() == 0)
    {
        m_attackChar = false;
        m_animState.Attack(false);
    }
}

void Zombie::removeFireballs()
{
    auto iter = remove_if(m_fireballAnimations.begin(), m_fireballAnimations.end(), [](const Fireball& ball)
    {
       return ball.IsAlive() == false;
    });
    m_fireballAnimations.erase(iter, m_fireballAnimations.end());
}

void Zombie::rangeAttack(const sf::RectangleShape& shape)
{
    if (false == m_attackChar)
    {
        return;
    }

    elapsed += 15ms;

    if (elapsed >= nextFireball)
    {
        Random random;
        nextFireball = random(1000ms, 1400ms);
        AttackChar(true);
        m_fireballAnimations.emplace_back(Fireball());
        m_fireballAnimations.back().Start({getPosition().x, getPosition().y},
                        {shape.getPosition().x, shape.getPosition().y - 50});

        elapsed = 0ms;
    }
    else
    {
        AttackChar(false);
    }
}



