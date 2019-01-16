#pragma once
#include <GameFramework/Framework/IScene.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Map.h"

class GameScene : public IScene
{
public:
    void Init() final override;
    void Deinit() final override;
    void Process() final override;
private:
    Map m_map;
};
