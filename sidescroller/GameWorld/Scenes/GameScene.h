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
    void Init() final override;
    void Deinit() final override;
    void Process() final override;
private:
    void resolveGravity();
//    void checkForMeleeIntersection();
    void checkForRangeIntersection();
    void handleFireball();
    void removeFireballs();

    void rangeAttack();
private:
    Map m_map;
    Knight m_knight;
    Zombie m_zombie;
    std::vector<Fireball> m_fireballAnimations;

    std::chrono::milliseconds elapsed = std::chrono::milliseconds::zero();
    std::chrono::milliseconds nextFireball = std::chrono::milliseconds(1000);
    bool animateBall = false;

    sf::Sprite fireSprite;
    sf::Sprite m_bloodSprite;
    std::map<std::string, Animation> bloodAnimations;
};
