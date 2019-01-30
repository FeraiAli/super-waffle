#include "GameScene.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>
#include <CharacterParser/CharacterParser.h>
#include <SFML/Window/Event.hpp>
#include <GameFramework/System/Random.h>
#include <iostream>
using namespace std::chrono_literals;


void GameScene::Init()
{
    m_map.Init();
    m_knight.Init();
    m_zombie.Init();
    m_fireballAnimations.reserve(64);
//    bloodAnimations["blood_a"].Init(GetAnimationFrames("blood", "blood_a"), 500ms);
//    bloodAnimations["blood_b"].Init(GetAnimationFrames("blood", "blood_b"), 500ms);
//    bloodAnimations["blood_c"].Init(getKeys("blood", "blood_c"), 700ms);
//    bloodAnimations["blood_d"].Init(getKeys("blood", "blood_d"), 700ms);
}

void GameScene::Deinit()
{
    m_map.SaveMap();
}

void GameScene::Process()
{
    auto& window = Context::Get<sf::RenderWindow>();
    m_map.Process(window);

    m_knight.Update();
    m_zombie.Update();
    resolveGravity();
    rangeAttack();

    for (auto& ball : m_fireballAnimations)
    {
        ball.Update(m_knight.bodyRect);
        ball.Draw(window);
    }
    removeFireballs();

    m_knight.Draw(window);
    m_zombie.Draw(window);
    window.draw(m_knight);
}

void GameScene::resolveGravity()
{
    auto& mapTiles = m_map.GetMapTiles();
    auto knightRect = m_knight.getGlobalBounds();
    m_knight.IsGrounded = false;
    for(auto& yTile : mapTiles)
    {
        for(auto& tiles : yTile)
        {
            sf::FloatRect tilesBox = {tiles.getPosition().x, tiles.getPosition().y,
                                     tiles.getGlobalBounds().width, tiles.getGlobalBounds().height};

            if (false == tilesBox.intersects(m_knight.getGlobalBounds()) or
                false == tiles.isBox)
            {
                continue;
            }

            auto offsetY = (knightRect.top + knightRect.height) - tilesBox.top;
            m_knight.setPosition(m_knight.getPosition().x, m_knight.getPosition().y - offsetY);
            m_knight.IsGrounded = true;
            break;
        }
    }
}

//void GameScene::checkForMeleeIntersection()
//{
//    if (m_zombie.getGlobalBounds().intersects(m_knight.getGlobalBounds()))
//    {
//        m_zombie.AttackChar(true);

//        Random random;
//        static auto bloodIter = bloodAnimations.find(random({"blood_a", "blood_b"}));;
//        m_bloodSprite.setScale({0.3f,0.3f});
//        m_bloodSprite.setOrigin(m_bloodSprite.getLocalBounds().width / 2,
//                                m_bloodSprite.getLocalBounds().height / 2);

//        if(false == bloodIter->second.IsRunning())
//        {
//            drawBlood = false;
//        }
//        else
//        {
//            drawBlood = true;
//            m_bloodSprite.setTexture(*bloodIter->second.Step(15ms));
//        }

//        if(bloodIter != bloodAnimations.end())
//        {
//            if(false == bloodIter->second.IsRunning())
//            {
//                bloodIter = bloodAnimations.find(random({"blood_a", "blood_b"}));
//                bloodIter->second.Start();
//                m_bloodSprite.setPosition(m_knight.getPosition().x + 10, m_knight.getPosition().y + 15);
//                m_bloodSprite.move(random(-2.0f, 4.0f), random(-5.0f, 10.0f));
//            }
//        }
//    }
//    else
//    {
//        drawBlood = false;
//        m_zombie.AttackChar(false);
//    }
//}

void GameScene::removeFireballs()
{
    auto iter = remove_if(m_fireballAnimations.begin(), m_fireballAnimations.end(), [](const Fireball& ball)
    {
       return ball.IsAlive() == false;
    });
    m_fireballAnimations.erase(iter, m_fireballAnimations.end());
}

void GameScene::rangeAttack()
{
    elapsed += 15ms;

    if (elapsed >= nextFireball)
    {
        m_zombie.AttackChar(true);
        m_fireballAnimations.emplace_back(Fireball());
        m_fireballAnimations.back().Start(m_knight.getPosition());

        elapsed = 0ms;
    }
    else
    {
        m_zombie.AttackChar(false);
    }
}


