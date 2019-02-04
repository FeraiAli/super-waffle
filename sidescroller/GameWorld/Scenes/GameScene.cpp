#include "GameScene.h"
#include <GameFramework/Framework/Context.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void GameScene::Init()
{
    m_map.Init();
    m_knight.Init();
    m_zombies.resize(3);
    m_zombies[0].Init({1100, 150});
    m_zombies[1].Init({1400, 386});
    m_zombies[2].Init({1100, 510});
}

void GameScene::Deinit()
{
    m_map.SaveMap();
}

void GameScene::Process()
{
    auto& window = Context::Get<sf::RenderWindow>();
    m_map.Process(window);

    m_knight.Update(m_zombies);
    for (auto& zombie : m_zombies)
    {
        zombie.Update(m_knight.bodyRect);
        zombie.Draw(window);
    }
    resolveGravity();
    m_knight.Draw(window);
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void GameScene::OnMouseEvent(const sf::Event::MouseButtonEvent &mouseEvent)
//{
//    if(mouseEvent.button == sf::Mouse::Left)
//    {

//    }
//}

//void GameScene::checkForMeleeIntersection()
//{
//    bloodAnimations["blood_a"].Init(GetAnimationFrames("blood", "blood_a"), 500ms);
//    bloodAnimations["blood_b"].Init(GetAnimationFrames("blood", "blood_b"), 500ms);
//    bloodAnimations["blood_c"].Init(getKeys("blood", "blood_c"), 700ms);
//    bloodAnimations["blood_d"].Init(getKeys("blood", "blood_d"), 700ms);


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



