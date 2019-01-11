#include "EntityFactory.h"
#include "GameFramework/Entita/Pool.h"
#include "GameFramework/Framework/Context.hpp"
#include "GameWorld/Components/Components.h"
#include "GameFramework/Framework/ResourcesMgr.h"

const sf::Vector2f EntitySettings::Size = {40, 40};

Entita::Entity::Ptr EntityFactory::CreateTile(sf::Vector2f pos)
{
    auto& pool = Context::Get<Entita::Pool>();

    auto entity = pool.CreateEntity();
    entity->AddComponent<Tile>();
    entity->AddComponent<Collidable>();
    entity->AddComponent<Drawable>();
    entity->AddComponent<Body>();

    auto& body = entity->GetComponent<Body>();
    body.setPosition(pos);
    body.size = EntitySettings::Size;

    auto texture = Context::Get<ResourcesMgr>().GetTexture("box");
    auto& drawable = entity->GetComponent<Drawable>();
    drawable.setPosition(pos);
    drawable.setTexture(*texture);
    drawable.setScale(EntitySettings::Size.x / drawable.getTextureRect().width,
                      EntitySettings::Size.y / drawable.getTextureRect().height);

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
    player->AddComponent<Drawable>();

    auto& body = player->GetComponent<Body>();
    body.size = EntitySettings::Size*2.0f;

    auto texture = Context::Get<ResourcesMgr>().GetTexture("attack1");
    auto& drawable = player->GetComponent<Drawable>();
    drawable.setPosition(pos);
    drawable.setTexture(*texture);
    drawable.setScale(body.size.x / drawable.getTextureRect().width,
                      body.size.y / drawable.getTextureRect().height);

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
    body.size = EntitySettings::Size*2.0f;

    auto& skin = enemy1->GetComponent<Skin>();
    skin.setSize(body.size);
    skin.setFillColor(sf::Color(200, 50, 50));

    return enemy1;
}
