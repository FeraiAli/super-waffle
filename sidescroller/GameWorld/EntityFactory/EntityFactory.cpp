#include "EntityFactory.h"
#include "GameFramework/Entita/Pool.h"
#include "GameFramework/Framework/Context.hpp"
#include "GameWorld/Components/Components.h"

const sf::Vector2f EntitySettings::Size = {40, 40};

Entita::Entity::Ptr EntityFactory::CreateTile(sf::Vector2f pos)
{
    auto& pool = Context::Get<Entita::Pool>();

    auto entity = pool.CreateEntity();
    entity->AddComponent<Tile>();
    entity->AddComponent<Collidable>();
    entity->AddComponent<Skin>();
    entity->AddComponent<Body>();

    auto& body = entity->GetComponent<Body>();
    body.setPosition(pos);
    body.size = EntitySettings::Size;

    auto& skin = entity->GetComponent<Skin>();
    skin.setPosition(pos);
    skin.setSize(EntitySettings::Size);
    skin.setFillColor(sf::Color(11, 102, 35));

    return entity;
}

Entita::Entity::Ptr EntityFactory::CreatePlayer1(sf::Vector2f pos)
{
    auto& pool = Context::Get<Entita::Pool>();

    auto player = pool.CreateEntity();
    player->AddComponent<Movable>();
    player->AddComponent<Jumpable>();
    player->AddComponent<Collidable>();
    player->AddComponent<Player>();
    player->AddComponent<Body>();
    player->AddComponent<Weapon>();
    player->AddComponent<Skin>();
    player->AddComponent<WASDController>();

    auto& skin = player->GetComponent<Skin>();
    skin.setPosition(pos);
    skin.setSize(EntitySettings::Size);
    skin.setFillColor(sf::Color::Green);

    auto& body = player->GetComponent<Body>();
    body.size = EntitySettings::Size;

    return player;
}

Entita::Entity::Ptr EntityFactory::CreatePlayer2(sf::Vector2f pos)
{
    auto player2 = CreatePlayer1(pos);
    player2->RemoveComponent<WASDController>();
    player2->AddComponent<ArrowController>();

    player2->GetComponent<Skin>().setFillColor(sf::Color::Magenta);
    return player2;
}

Entita::Entity::Ptr EntityFactory::CreateEnemy(sf::Vector2f pos)
{
    auto& pool = Context::Get<Entita::Pool>();

    auto enemy1 = pool.CreateEntity();
    enemy1->AddComponent<Movable>();
    enemy1->AddComponent<Collidable>();
    enemy1->AddComponent<Enemy>();
    enemy1->AddComponent<Body>();
    enemy1->AddComponent<Skin>();

    auto& body = enemy1->GetComponent<Body>();
    body.setPosition(pos);
    body.size = EntitySettings::Size;

    auto& skin = enemy1->GetComponent<Skin>();
    skin.setOutlineColor(sf::Color::Black);
    skin.setOutlineThickness(2.0f);
    skin.setSize(EntitySettings::Size);
    skin.setFillColor(sf::Color(200, 50, 50));

    return enemy1;
}
