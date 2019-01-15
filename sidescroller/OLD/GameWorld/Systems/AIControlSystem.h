#pragma once
#include <GameFramework/Entita/BaseSystem.h>

namespace Entita
{
    class Entity;
}

class AIControlSystem: public Entita::BaseSystem
{
public:
    void Process() override;
private:
    using EntityPtr = std::shared_ptr<Entita::Entity>;
    void handleSimpleAIController(EntityPtr entity);
};
