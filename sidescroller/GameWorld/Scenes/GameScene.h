#pragma once
#include <GameFramework/Framework/IScene.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"
#include "CharacterInfo.h"
#include "Map.h"
#include <map>

class GameScene : public IScene
{
public:
    void Init() final override;
    void Deinit() final override;
    void Process() final override;
    void zombieProcess();
private:
    Map m_map;
    CharacterInfo m_character;

    std::map<std::string, Animation> knightAnimations;
    std::map<std::string, Animation> zombieAnimations;

    std::string newAnimation = "idle";
    std::string  currentAnimation = "idle";

    sf::Sprite characterSprite;
    sf::Sprite zombieSprite;

};
