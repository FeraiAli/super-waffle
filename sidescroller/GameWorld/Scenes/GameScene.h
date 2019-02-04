#pragma once
#include <GameFramework/Framework/IScene.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.h"
#include "Fireball.h"
#include "Map.h"
#include <map>
#include "Knight.h"
#include "Zombie.h"

class GameScene : public IScene
{
public:
    using ZombieContainer = std::vector<Zombie>;

    void Init() final override;
    void Deinit() final override;
    void Process() final override;
//    void OnMouseEvent(const sf::Event::MouseButtonEvent& mouseEvent) override;
private:
    void resolveGravity();
//    void checkForMeleeIntersection();
private:
    Map m_map;
    Knight m_knight;
    ZombieContainer m_zombies;
//    std::map<std::string, Animation> bloodAnimations;
};
