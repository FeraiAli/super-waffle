#pragma once
#include <GameFramework/Entita/BaseSystem.h>
#include <GameFramework/System/Random.h>

class EnemySpawnSystem : public Entita::BaseSystem
{
public:
    void Process() override;
private:
    Random m_random;
    void CreateSimpleEnemy();
};
