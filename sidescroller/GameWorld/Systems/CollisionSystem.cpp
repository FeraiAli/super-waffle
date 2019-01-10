#include "CollisionSystem.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Components/Components.h"

#include <cmath>

//namespace AABBResolver
//{

//struct CollisionInfo
//{
//    sf::FloatRect bounds;
//    float area = 0.0f;
//};

//void resoloveCollision(Entita::Entity::Ptr agent, std::vector<CollisionInfo>&& collisions)
//{
//    if(collisions.empty())
//    {
//        return;
//    }

//    std::sort(collisions.begin(), collisions.end(), [](const auto& info1, const auto& info2)
//    {
//        return info1.area < info2.area;
//    });

//    auto& agentBody = agent->GetComponent<Body>();
//    for(auto& info : collisions)
//    {
//        sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
//                                  agentBody.size.x, agentBody.size.y};

//        if(false == agentBox.intersects(info.bounds))
//        {
//            continue;
//        }

//        float xDiff = (agentBox.left + (agentBox.width / 2)) -
//                      (info.bounds.left + (info.bounds.width / 2));

//        float yDiff = (agentBox.top + (agentBox.height / 2)) -
//                      (info.bounds.top + (info.bounds.height / 2));

//        float resolve = 0.0f;
//        if(std::abs(xDiff) > std::abs(yDiff))
//        {
//            if(xDiff > 0.0f)
//            {
//                resolve = (info.bounds.left + info.bounds.width) - agentBox.left;
//            }
//            else
//            {
//                resolve = -((agentBox.left + agentBox.width) - info.bounds.left);
//            }
//            agentBody.move(resolve, 0.0f);
//            agentBody.velocity.x = 0.0f;
//        }
//        else
//        {
//            if(yDiff > 0.0f)
//            {
//                resolve = (info.bounds.top + info.bounds.height) - agentBox.top;
//            }
//            else
//            {
//                resolve = -((agentBox.top + agentBox.height) - info.bounds.top);
//            }
//            agentBody.move(0.0f, resolve);
//            agentBody.velocity.y = 0.0f;
//        }
//    }
//}
//} //end of namespace AABBResolver

void CollisionSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();

    auto tiles = pool.GetEntities<Tile>();
    auto agents = pool.GetEntities<Agent>();

    for(auto& agent : agents)
    {
        auto& agentBody = agent->GetComponent<Body>();
        agentBody.isGrounded = false;
        sf::FloatRect agentBox = {agentBody.getPosition().x, agentBody.getPosition().y,
                                  agentBody.size.x, agentBody.size.y};

        //std::vector<AABBResolver::CollisionInfo> collisionInfo;
        for(const auto& tile : tiles)
        {
            const auto& tileBody = tile->GetComponent<Body>();
            sf::FloatRect tileBox = {tileBody.getPosition().x,tileBody.getPosition().y,
                                     tileBody.size.x, tileBody.size.y};

            sf::FloatRect intersectArea;
            agentBox.intersects(tileBox, intersectArea);

            //AABBResolver::CollisionInfo colInfo;
            //colInfo.bounds = tileBox;
            //colInfo.area = intersectArea.width * intersectArea.height;

            //collisionInfo.emplace_back(std::move(colInfo));

            const auto agentBottomPos = agentBox.top + agentBox.height + 10;
            const auto agentCenterX = agentBox.left + (agentBox.width / 2);
            if(tileBox.contains(agentCenterX, agentBottomPos))
            {
                agentBody.isGrounded = true;
            }
        }
        //AABBResolver::resoloveCollision(agent, std::move(collisionInfo));
    }
}


