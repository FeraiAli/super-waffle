#pragma once
#include <GameFramework/Entita/Pool.h>
#include <GameFramework/Framework/IScene.h>

class GameScene : public IScene
{
public:
    void Init() final override;
    void Show() final override;
    void Hide() final override;
    void Process() final override;
private:
};
