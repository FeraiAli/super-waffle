#pragma once
#include <GameFramework/Entita/BaseSystem.h>
#include <GameFramework/Entita/Entity.h>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class CollisionSystem : public Entita::BaseSystem
{
public:
    void Process() override;
};
