#include "Body.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <GameFramework/Framework/Context.hpp>
#include <PhysicsBox2D/Box2DWorld.h>

Body::Body(sf::Vector2f sz, Type type)
    : size(sz)
{
    auto& world = Context::Get<Box2DWorld>();

    b2BodyType bodyType = b2BodyType::b2_staticBody;
    if(Type::Dynamic == type) bodyType = b2BodyType::b2_dynamicBody;

    body = world.CreateBody(size, bodyType);
}

Body::~Body()
{
    auto& world = Context::Get<Box2DWorld>();
    world.Get()->DestroyBody(body);
}

void Body::setPosition(sf::Vector2f pos)
{
    body->SetTransform({pos.x, pos.y}, 0.0f);
}

void Body::setPosition(float x, float y)
{
    body->SetTransform({x, y}, 0.0f);
}

sf::Vector2f Body::getPosition() const
{
    return {body->GetPosition().x, body->GetPosition().y};
}

void Body::updatePositions()
{
    body->SetLinearVelocity({velocity.x, velocity.y});
}
