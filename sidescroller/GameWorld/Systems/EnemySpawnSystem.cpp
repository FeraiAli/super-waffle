#include "EnemySpawnSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>
#include "../Components/Components.h"

#include <chrono>
using namespace std::chrono_literals;

namespace Settings
{
    const std::chrono::milliseconds TimeSpawn = 1s;
    std::chrono::milliseconds TimeSpawnCounter = 0ms;
}

void EnemySpawnSystem::Process()
{
    Settings::TimeSpawnCounter += 15ms;

    if (Settings::TimeSpawnCounter >= Settings::TimeSpawn )
    {
        Settings::TimeSpawnCounter = 0ms;
        CreateSimpleEnemy();
    }
}

void EnemySpawnSystem::CreateSimpleEnemy()
{
    const auto color = m_random({sf::Color(220,220,220), sf::Color::Red, sf::Color(100, 100, 100)});
    const auto pos = m_random(sf::Vector2f(100, 50), sf::Vector2f(1300, 50));

    auto& pool = Context::Get<Entita::Pool>();
    auto enemy1 = pool.CreateEntity();
    enemy1->AddComponent<Movable>();
    enemy1->AddComponent<Collidable>();
    const auto maxSpeed = enemy1->AddComponent<Enemy>().MaxGroundSpeed;
    enemy1->AddComponent<SimpleAIController>();

    auto& body = enemy1->AddComponent<Body>();
    body.setPosition(pos);
    body.velocity.x = m_random(0.5) ? -maxSpeed : maxSpeed;

    auto& skin = enemy1->AddComponent<Skin>();
    skin.setFillColor(color);
    skin.setOutlineColor(sf::Color::Black);
    skin.setOutlineThickness(2.0f);
}

