#pragma once
#include "KnightAnimationState.h"
#include "CharacterInfo.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Zombie.h"
#include "Slash.h"
#include "HealthBar.h"
#include <memory>

class Knight : public sf::Sprite
{
public:
    using Duration = std::chrono::milliseconds;
    void Init();
    void Update(std::vector<Zombie>& zombies);
    void ResolveCollision();
    void HandleJump();
////////////////////////////////////////////
    void Draw(sf::RenderWindow& window);
////////////////////////////////////////////
    bool IsGrounded = true;
    sf::RectangleShape bodyRect;
private:
    void removeSlashes();
    void updateBodyRect(std::vector<Zombie>& zombies);
private:
    bool isJumping = false;
    sf::Vector2f m_velocity = {};
    const float slashSpeed = 12.f;

    HealthBar m_healthBar;
    std::vector<Slash> m_slashes;
    KnightAnimationState m_animState;
    Duration jumpTimeCounter = Duration::zero();
};
