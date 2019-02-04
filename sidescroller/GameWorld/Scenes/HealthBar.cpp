#include "HealthBar.h"
#include "GameFramework/Framework/ResourcesMgr.h"
#include <GameFramework/Framework/Context.hpp>
#include <algorithm>

void HealthBar::Init(sf::Vector2f pos)
{
    auto& resMgr = Context::Get<ResourcesMgr>();
    auto redTexture = resMgr.GetTexture("redHealth");
    auto greenTexture = resMgr.GetTexture("greenHealth");
    red.setTexture(*redTexture);
    green.setTexture(*greenTexture);
    red.setPosition(pos);
    green.setPosition(pos);
    red.setScale(0.1f,0.3f);
    green.setScale(0.1f,0.3f);
}

void HealthBar::Update(sf::Vector2f pos)
{
    red.setPosition(pos);
    green.setPosition(pos);
}

void HealthBar::ChangeHealth()
{
    m_currentHealth = std::max(0, m_health -= 100);
    green.setTextureRect(sf::IntRect(0, 0, m_currentHealth, 50));
}

int HealthBar::GetCurrentHealth()
{
    return m_currentHealth;
}

void HealthBar::Draw(sf::RenderWindow &window)
{
    window.draw(red);
    window.draw(green);
}
