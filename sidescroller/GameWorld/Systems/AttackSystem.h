#pragma once
#include <GameFramework/Entita/BaseSystem.h>
#include <GameFramework/Entita/Entity.h>
#include <chrono>

class AttackSystem : public Entita::BaseSystem
{
public:
    void Process() override;
private:
    void handleGunAttack(Entita::Entity::Ptr entity);
};
