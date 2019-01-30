#include "Knight.h"
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cmath>
#include "AnimationUtilities.h"
using namespace std::chrono_literals;

namespace Settings
{
    const float AirSpeed = 8.0f;
    const float JumpSpeed = 6.5f;
    const float GroundSpeed = 7.0f;
    const float MaxSpeed = 9.0f;
    const float MaxFallingSpeed = 16.0f;
    const float Gravity = 0.5f;
    const std::chrono::milliseconds JumpTime = 160ms;
    const std::chrono::milliseconds AfterFallingJumpDelay = 60ms;
}

void Knight::Init()
{
    m_animState.Init();
    setScale({0.2f, 0.2f});
    setPosition(300, 750);
    txtShield.loadFromFile("../sidescroller/Assets/shields.png");
    shield.setTexture(txtShield);
}

void Knight::Update()
{
    CharacterInfo info;
    info.isGrounded = IsGrounded;
    m_velocity.x = 0.0f;

    if(false == m_animState.IsAttacking())
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            info.isAttacking = true;
        }
        if(info.isGrounded and sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            isJumping = true;
            m_velocity.y = -Settings::JumpSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_velocity.x = -MOVE_SPEED;
            setScale(-0.2f, 0.2f);
            info.isMoving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_velocity.x = MOVE_SPEED;
            setScale(0.2f, 0.2f);
            info.isMoving = true;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            drawShield = true;
            shield.setScale(0.6f, 0.6f);
            shield.setOrigin(shield.getGlobalBounds().width / 2,
                             shield.getGlobalBounds().height / 2);
        }
        else
        {
            drawShield = false;
        }
    }

    if(isJumping)
    {
        HandleJump();
    }
    else if(false == isJumping)
    {
        jumpTimeCounter = 0ms;
        if (false == IsGrounded)
        {
            m_velocity.y += Settings::Gravity;
        }
    }

    updateBodyRect();
    move(m_velocity.x, m_velocity.y);
    m_animState.Update(info);
    setTexture(*m_animState.GetTexture());
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

void Knight::HandleJump()
{
    jumpTimeCounter += 15ms;

    if(jumpTimeCounter >= Settings::JumpTime)
    {
        isJumping = false;
    }
}

void Knight::SetVelocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Knight::Draw(sf::RenderWindow &window)
{
    if (drawShield)
    {
        window.draw(shield);
    }
}

void Knight::speedConstrainst()
{
    m_velocity.x = std::min(m_velocity.x, Settings::MaxSpeed);
    m_velocity.x = std::max(m_velocity.x, -Settings::MaxSpeed);

    m_velocity.y = std::min(m_velocity.y, Settings::MaxFallingSpeed);
}

void Knight::speedDecrease()
{
    if ((m_velocity.y < 0.0f) and
        (m_velocity.y > (-4)) and
        (std::abs(m_velocity.x) > 0.125f))
    {
        m_velocity.x *= 0.94875f;
    }
}

void Knight::updateBodyRect()
{
    bodyRect.setSize({getGlobalBounds().width - 45, getGlobalBounds().height - 55});
    bodyRect.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
    bodyRect.setFillColor(sf::Color::White);
    bodyRect.setPosition(getPosition().x + 15, getPosition().y + 15);
    shield.setPosition(bodyRect.getPosition().x - 50,
                       bodyRect.getPosition().y - 40);
}


