#include "Slash.h"
#include "GameFramework/Framework/ResourcesMgr.h"
#include <GameFramework/Framework/Context.hpp>

void Slash::Start(const sf::Vector2f &pos, const float& scale, const float& speed)
{
    m_alive = true;
    auto& resMgr = Context::Get<ResourcesMgr>();
    auto texture = resMgr.GetTexture("slash1");
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(pos.x - 5, pos.y - 40);
    m_sprite.setScale(scale,0.3f);
    m_speed = speed;
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2,
                       m_sprite.getGlobalBounds().height / 2);
    m_rect.setSize({80, 40});
    if (scale < 0) { m_rect.setOrigin(m_rect.getGlobalBounds().width, 0); }
    m_rect.setPosition(pos.x - 5, pos.y - 40);
}

void Slash::Update(std::vector<Zombie>& zombies)
{
    if (interaction(zombies))
    {
        m_alive = false;
    }
    m_sprite.move(m_speed, 0.0f);
    m_rect.move(m_speed, 0.0f);
    outOfBounds();
}

void Slash::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

bool Slash::IsAlive() const
{
    return m_alive;
}

void Slash::outOfBounds()
{
    auto posX = m_rect.getPosition().x;
    auto posY = m_rect.getPosition().y;
    auto rect = m_rect.getGlobalBounds();

    if ((posX + (rect.width / 2)) < 0 or (posX - (rect.width / 2)) > 1600)
    {
        m_alive = false;
    }
    if ((posY + rect.height / 2) < 0 or (posY - rect.height/ 2) > 900)
    {
        m_alive = false;
    }
}

bool Slash::interaction(std::vector<Zombie>& zombies)
{
    for (auto& zombie : zombies)
    {
        if (m_rect.getGlobalBounds().intersects(zombie.bodyRect.getGlobalBounds()))
        {
            zombie.GetHealthBar().ChangeHealth();
            return true;
        }
    }
    return false;
}

