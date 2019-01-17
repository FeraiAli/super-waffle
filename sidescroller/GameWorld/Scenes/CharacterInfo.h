#pragma once
#include <SFML/System/Vector2.hpp>

struct CharacterInfo
{
    enum FaceDirection {Left, Right};

    bool isGrounded = true;
    bool isJumping = false;
    bool isMoving = false;
    bool isAttacking = false;
    FaceDirection direction = FaceDirection::Left;

    sf::Vector2f velocity = {};
    sf::Vector2f scale = {0.2f,0.2f};
};
