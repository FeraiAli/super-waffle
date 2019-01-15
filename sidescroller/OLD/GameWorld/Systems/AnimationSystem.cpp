#include "AnimationSystem.h"

#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Entita/Pool.h>
#include <GameFramework/Framework/ResourcesMgr.h>
#include "../Components/Components.h"
#include <GameFramework/Math/RangeMap.hpp>
#include <chrono>
#include <cmath>
#include <SFML/Window/Event.hpp>

using namespace std::chrono_literals;

void AnimationSystem::Process()
{
    auto& pool = Context::Get<Entita::Pool>();
    auto& resMgr = Context::Get<ResourcesMgr>();
    for(auto entity : pool.GetEntities<Drawable>())
    {
        auto& drawable = entity->GetComponent<Drawable>();
        if(false == drawable.HasAnimation())
        {
            continue;
        }

        auto currentAnim = drawable.GetCurrentAnimation();

        currentAnim->second.elapsed += 15ms;
        if(currentAnim->second.elapsed >= currentAnim->second.duration)
        {
            currentAnim->second.elapsed = 0ms;
        }

//        if(currentAnim->first != "attack")
//        {
            if(entity->HasComponent<Body>())
            {
                auto& body = entity->GetComponent<Body>();
                if("idle" == currentAnim->first)
                {
                    if(std::abs(body.velocity.x) > 0.0f)
                    {
                        drawable.SetAnimation("run");
                        if(body.faceDir == Body::FaceDirection::Left)
                        {   
//                            drawable.setScale(-drawable.getScale().x, drawable.getScale().y);
                        }
                        else
                        {
//                            drawable.setScale(std::abs(drawable.getScale().x), drawable.getScale().y);
                        }
                    }
                    if(std::abs(body.velocity.y) > 0.0f)
                    {
                        drawable.SetAnimation("jump");
                    }
                }
                else if("run" == currentAnim->first)
                {
                    if(body.velocity.x == 0.0f)
                    {
                        drawable.SetAnimation("idle");
                    }
                }
                else if("jump" == currentAnim->first)
                {
                    if(body.velocity.y == 0.0f)
                    {
                        drawable.SetAnimation("idle");
                    }
                }
            }
//        }

        if(entity->HasComponent<Weapon>())
        {
            if(entity->GetComponent<Weapon>().onAttackBegin)
            {
                drawable.SetAnimation("attack");
            }
        }

        auto currentFrameId = Math::RangeMap(currentAnim->second.elapsed.count(), int64_t(0), currentAnim->second.duration.count(),
                                             0ul, currentAnim->second.frames.size() - 1);

        auto currentAnimId = currentAnim->second.frames[currentFrameId];

        drawable.setTexture(*resMgr.GetTexture(currentAnimId));
    };

}
