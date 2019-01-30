#pragma once
#include "KnightAnimationState.h"
#include "CharacterInfo.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Knight : public sf::Sprite
{
public:
    using Duration = std::chrono::milliseconds;
    void Init();
    void Update();
    void ResolveCollision();
    void HandleJump();
    void SetVelocity(sf::Vector2f velocity);
////////////////////////////////////////////
    void Draw(sf::RenderWindow& window);
    void HandleFireAnimation();
////////////////////////////////////////////
    bool IsGrounded = true;
    sf::RectangleShape bodyRect;
private:
    void speedConstrainst();
    void speedDecrease();
    void updateBodyRect();
private:
///////////////////////////////////
    sf::Sprite shield;
    sf::Texture txtShield;
    bool drawShield = false;
///////////////////////////////////
    bool isJumping = false;
    KnightAnimationState m_animState;
    static constexpr float MOVE_SPEED = 5.0f;

    sf::Vector2f m_velocity = {};
    Duration jumpTimeCounter = Duration::zero();
};
