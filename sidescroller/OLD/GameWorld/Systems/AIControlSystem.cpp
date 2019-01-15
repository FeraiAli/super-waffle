#include "AIControlSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include "../Components/Components.h"

void AIControlSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();

    for (auto entity : pool.GetEntities<Enemy, Body, Collidable>())
    {
        if(entity->HasComponent<SimpleAIController>())
        {
            handleSimpleAIController(entity);
        }
    }
}

void AIControlSystem::handleSimpleAIController(AIControlSystem::EntityPtr entity)
{
    const auto& enemy = entity->GetComponent<Enemy>();
    auto& body = entity->GetComponent<Body>();
    const auto& collidable = entity->GetComponent<Collidable>();

    if(collidable.Has(CollisionSide::Left))
    {
        body.velocity.x = enemy.MaxGroundSpeed;
    }
    else if(collidable.Has(CollisionSide::Right))
    {
        body.velocity.x = -enemy.MaxGroundSpeed;
    }
}
