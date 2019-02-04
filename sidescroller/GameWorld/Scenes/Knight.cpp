#include "Knight.h"
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cmath>
#include "AnimationUtilities.h"
using namespace std::chrono_literals;

namespace Settings
{
    const float Gravity = 0.5f;
    const float MoveSpeed = 5.0f;
    const float JumpSpeed = 6.5f;
    const std::chrono::milliseconds JumpTime = 160ms;
}

void Knight::Init()
{
    m_animState.Init();

    setScale({0.2f, 0.2f});
    setPosition(300, 750);
//    m_healthBar.Init({250, 670});

    bodyRect.setSize({getGlobalBounds().width - 60, getGlobalBounds().height - 70});
    bodyRect.setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
    bodyRect.setFillColor(sf::Color::White);
}

void Knight::Update(std::vector<Zombie>& zombies)
{
    CharacterInfo info;
    info.isGrounded = IsGrounded;
    m_velocity.x = 0.0f;

    if(false == m_animState.IsAttacking())
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            info.isAttacking = true;
            m_slashes.emplace_back(Slash());
            auto scale = getScale().x > 0 ? 0.3f : -0.3f;
            auto speed = scale > 0 ? slashSpeed : -slashSpeed;
            m_slashes.back().Start({bodyRect.getPosition().x, bodyRect.getPosition().y}, scale, speed);
        }

        if(info.isGrounded and sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            isJumping = true;
            m_velocity.y = -Settings::JumpSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_velocity.x = -Settings::MoveSpeed;
            setScale(-0.2f, 0.2f);
            info.isMoving = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_velocity.x = Settings::MoveSpeed;
            setScale(0.2f, 0.2f);
            info.isMoving = true;
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

//    m_healthBar.Update({getPosition().x - 50, getPosition().y - 80});
    updateBodyRect(zombies);
    removeSlashes();
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

void Knight::Draw(sf::RenderWindow &window)
{
//    window.draw(bodyRect);
//    m_healthBar.Draw(window);
    for (auto& slash : m_slashes)
    {
        slash.Draw(window);
    }
}

void Knight::updateBodyRect(std::vector<Zombie>& zombies)
{
    bodyRect.setPosition(getPosition().x + 25, getPosition().y + 35);
    for (auto& slash : m_slashes)
    {
        slash.Update(zombies);
    }
}

void Knight::removeSlashes()
{
    auto iter = remove_if(m_slashes.begin(), m_slashes.end(), [](const Slash& slash)
    {
       return slash.IsAlive() == false;
    });
    m_slashes.erase(iter, m_slashes.end());
}



