#pragma once
#include <SFML/System/Vector2.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <memory>

class Box2DWorld
{
public:
    Box2DWorld();
    void Process();
    std::unique_ptr<b2World>& Get();

    b2Body* CreateBody(sf::Vector2f size, b2BodyType type);
private:
    std::unique_ptr<b2World> m_b2World;
};
