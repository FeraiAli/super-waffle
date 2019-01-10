#include "AttackSystem.h"
#include <SFML/Window/Event.hpp>
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include "../Components/Components.h"

namespace
{
    bool IsAttackPreesed(Entita::Entity::Ptr entity)
    {
        sf::Keyboard::Key attackKey = sf::Keyboard::Unknown;

        if(entity->HasComponent<WASDController>())
        {
            attackKey = sf::Keyboard::Q;
        }
        else if(entity->HasComponent<ArrowController>())
        {
            attackKey = sf::Keyboard::RControl;
        }
        return sf::Keyboard::isKeyPressed(attackKey);
    }
}

void AttackSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();

    for(auto entity : pool.GetEntities<Body, Weapon>())
    {
        auto& weapon = entity->GetComponent<Weapon>();
        if(weapon.ReadyToAttack())
        {
            weapon.delayToAttackCounter = Weapon::Duration(0);
            if(weapon.type == Weapon::Type::Gun)
            {
                handleGunAttack(entity);
            }
        }
        else
        {
            weapon.delayToAttackCounter += Weapon::Duration(15);
        }
    };
}

void AttackSystem::handleGunAttack(Entita::Entity::Ptr entity)
{
    if(false == IsAttackPreesed(entity))
    {
        return;
    }

    auto& pool = Context::Get<Entita::Pool>();
    auto& entityBody = entity->GetComponent<Body>();
    auto bullet = pool.CreateEntity();
    bullet->Owner = entity;
    bullet->AddComponent<Collidable>();
    bullet->AddComponent<Bullet>();

    auto& movable = bullet->AddComponent<Movable>();
    movable.ignoreGravity = true;

    auto& body = bullet->AddComponent<Body>();
    body.setPosition(entityBody.getPosition().x, entityBody.getPosition().y);
    body.size = {5,5};

    if(entityBody.faceDir == Body::FaceDirection::Left)
    {
        body.velocity.x = -10.0f;
        entityBody.move(2.0f, 0.0f);
    }
    else
    {
        body.velocity.x = 10.0f;
        entityBody.move(-2.0f, 0.0f);
    }

    auto& skin = bullet->AddComponent<Skin>();
    skin.setFillColor(sf::Color::Red);
    skin.setOutlineColor(sf::Color::Black);
    skin.setOutlineThickness(1.0f);
}
