#pragma once
#include <GameFramework/Entita/BaseSystem.h>
#include <GameWorld/Components/Body.h>

namespace Entita
{
    class Entity;
    class Pool;
}

class MoveSystem : public Entita::BaseSystem
{
public:
    void Process() override;
private:
    using EntityPtr = std::shared_ptr<Entita::Entity>;
    void handleJumpAndMovement(EntityPtr entity, Body& body);

    void handleGroundMovement(EntityPtr entity, Body& body);
    void handleAirMovement(EntityPtr entity, Body& body);

    void speedDecrease(Body& body);
    void speedConstraints(Body& body);
};
