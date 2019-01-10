#include "Box2DWorld.h"
#include <Box2D/Box2D.h>

namespace Settings
{
    const b2Vec2 gravity = {0.0f, 0.0f};
    const constexpr float timeStep = 1.0f / 60.0f;
    const int32_t velocityIterations = 8;
    const int32_t positionIterations = 3;

    const constexpr float physicWorldScale = 30.0f;
}


float PixelToMeter(float pixel)
{
    return pixel * (1.0f / Settings::physicWorldScale);
}

float MeterToPixel(float meter)
{
    return meter * Settings::physicWorldScale;
}

std::unique_ptr<b2World>& Box2DWorld::Get()
{
    return m_b2World;
}

b2Body* Box2DWorld::CreateBody(sf::Vector2f size, b2BodyType type)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(PixelToMeter(size.x / 2), PixelToMeter(size.y / 2));

    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = &shape;
    bodyFixtureDef.density = 1.0f;

    auto body = m_b2World->CreateBody(&bodyDef);
    body->CreateFixture(&bodyFixtureDef);

    shape.SetAsBox(PixelToMeter(size.x / 3), PixelToMeter(10.0f), b2Vec2{0.0f, 1.45f}, 0);
    return body;
}

Box2DWorld::Box2DWorld()
    : m_b2World(std::make_unique<b2World>(Settings::gravity))
{

}

void Box2DWorld::Process()
{
    m_b2World->Step(Settings::timeStep, Settings::positionIterations, Settings::velocityIterations);
}
