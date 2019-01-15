#include "CollisionSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/Components.h"

#include <cmath>

namespace AABBResolver
{

struct CollisionInfo
{
    sf::FloatRect bounds;
    float area = 0.0f;
};

void resoloveCollision(Entita::Entity::Ptr agent, std::vector<CollisionInfo>&& collisions)
{
    if(collisions.empty())
    {
        return;
    }

    std::sort(collisions.begin(), collisions.end(), [](const auto& info1, const auto& info2)
    {
        return info1.area > info2.area;
    });

    auto& agentBody = agent->GetComponent<Body>();
    auto& collidable = agent->GetComponent<Collidable>();
    collidable.Reset();

    for(auto& info : collisions)
    {
        sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
                                  agentBody.size.x, agentBody.size.y};

        if(false == agentBox.intersects(info.bounds))
        {
            continue;
        }

        float xDiff = (agentBox.left + (agentBox.width / 2)) -
                      (info.bounds.left + (info.bounds.width / 2));

        float yDiff = (agentBox.top + (agentBox.height / 2)) -
                      (info.bounds.top + (info.bounds.height / 2));

        float resolve = 0.0f;
        if(std::abs(xDiff) > std::abs(yDiff))
        {
            if(xDiff > 0.0f)
            {
                collidable.Add(CollisionSide::Left);
                resolve = (info.bounds.left + info.bounds.width) - agentBox.left;
            }
            else
            {
                collidable.Add(CollisionSide::Right);
                resolve = -((agentBox.left + agentBox.width) - info.bounds.left);
            }
            agentBody.move(resolve, 0.0f);
            agentBody.velocity.x = 0.0f;
        }
        else
        {
            if(yDiff > 0.0f)
            {
                collidable.Add(CollisionSide::Top);
                resolve = (info.bounds.top + info.bounds.height) - agentBox.top;
            }
            else
            {
                resolve = -((agentBox.top + agentBox.height) - info.bounds.top);
            }
            agentBody.move(0.0f, resolve);
            agentBody.velocity.y = 0.0f;

            collidable.Add(CollisionSide::Down);
        }
    }
}
} //end of namespace AABBResolver

void CollisionSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();

    auto tiles = pool.GetEntities<Tile, Body, Collidable>();
    auto players = pool.GetEntities<Player, Body, Collidable>();
    auto enemies = pool.GetEntities<Enemy, Body, Collidable>();

    handleAgentToTile(tiles, enemies);
    handleAgentToTile(tiles, players);

    auto bullets = pool.GetEntities<Bullet>();
    for(auto iter = bullets.begin(); iter != bullets.end(); ++iter)
    {
        if((*iter)->Owner.lock()->HasComponent<Player>())
        {
            handleBulletToAgents((*iter), enemies);
        }
    }

    //handleEnemiesToPlayer(players, enemies);
}

void CollisionSystem::handleAgentToTile(const CollisionSystem::EntityList& tiles,
                                        const CollisionSystem::EntityList& agents)
{
    for(auto& agent : agents)
    {
        auto& agentBody = agent->GetComponent<Body>();
        sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
                                  agentBody.size.x, agentBody.size.y};

        std::vector<AABBResolver::CollisionInfo> collisionInfo;
        for(const auto& tile : tiles)
        {
            const auto& tileBody = tile->GetComponent<Body>();
            sf::FloatRect tileBox = {tileBody.getPosition().x,tileBody.getPosition().y,
                                     tileBody.size.x, tileBody.size.y};

            sf::FloatRect intersectArea;
            agentBox.intersects(tileBox, intersectArea);

            AABBResolver::CollisionInfo colInfo;
            colInfo.bounds = tileBox;
            colInfo.area = intersectArea.width * intersectArea.height;

            collisionInfo.emplace_back(std::move(colInfo));

        }
        AABBResolver::resoloveCollision(agent, std::move(collisionInfo));
    }
}

void CollisionSystem::handleBulletToAgents(Entita::Entity::Ptr bullet, const CollisionSystem::EntityList &agents)
{
    auto& pool = Context::Get<Entita::Pool>();

    auto& bulletBody = bullet->GetComponent<Body>();
    sf::FloatRect bulletBox = {bulletBody.getPosition().x, bulletBody.getPosition().y,
                              bulletBody.size.x, bulletBody.size.y};

    for(auto iter = agents.begin(); iter != agents.end(); ++iter)
    {
        auto& agentBody = (*iter)->GetComponent<Body>();
        sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
                                  agentBody.size.x, agentBody.size.y};
        if(bulletBox.intersects(agentBox))
        {
            pool.RemoveEntity(bullet);
            pool.RemoveEntity((*iter));
        }
    }
}

