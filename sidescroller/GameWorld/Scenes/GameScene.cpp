#include "GameScene.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>
#include <CharacterParser/CharacterParser.h>
#include <SFML/Window/Event.hpp>
#include <iostream>
using namespace std::chrono_literals;
void GameScene::Init()
{
    m_map.Init();

    auto getKeys = [](std::string name, std::string animId)
    {
        const auto& parser = Context::Get<Parser::CharacterParser>();
        std::vector<std::string> result;
        for(auto& key : parser.GetTexturePaths(name, animId))
        {
            result.push_back(key);
        }
        return result;
    };

    knightAnimations["idle"].Init(getKeys("knight", "idle"), 600ms);
    knightAnimations["run"].Init(getKeys("knight", "run"), 500ms);
    knightAnimations["jump"].Init(getKeys("knight", "jump"), 500ms);
    knightAnimations["attack"].Init(getKeys("knight", "attack"), 500ms, false);
    characterSprite.setPosition(300, 750);

    zombieAnimations["idle"].Init(getKeys("female_zombie", "idle"), 700ms);
    zombieSprite.setPosition(600, 770);
}

void GameScene::Deinit()
{
    m_map.SaveMap();
}

void GameScene::Process()
{
    auto& window = Context::Get<sf::RenderWindow>();
    m_map.Process(window);
    m_character.velocity = {};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_character.velocity.x += 5.0f;
        m_character.scale.x = 0.2f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_character.velocity.x -= 5.0f;
        m_character.scale.x = -0.2f;
    }

    if(m_character.velocity.x != 0.0f) { currentAnimation = "run";  }
    if(m_character.velocity.x == 0.0f and currentAnimation != "attack")
    {
        currentAnimation = "idle";
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        currentAnimation = "attack";
        auto iter = knightAnimations.find(currentAnimation);
        if(iter != knightAnimations.end() and iter->second.IsFinished())
        {
            iter->second.Start();
        }
    }

    auto iter = knightAnimations.find(currentAnimation);
    if(iter != knightAnimations.end())
    {
        if(iter->second.IsFinished())
        {
            if(iter->second.IsRepeatable())
            {
                iter->second.Start();
            }
            else
            {
                currentAnimation = "idle";
            }
        }
        else
        {
            characterSprite.setTexture(*iter->second.Step(15ms));
        }
    }

    characterSprite.setScale({m_character.scale.x, 0.2f});
    characterSprite.setOrigin(characterSprite.getLocalBounds().width / 2,
                              characterSprite.getLocalBounds().height / 2);
    characterSprite.move(m_character.velocity);

    window.draw(characterSprite);
    zombieProcess();
}

void GameScene::zombieProcess()
{
    std::string currentAnimation = "idle";
    auto iter = zombieAnimations.find(currentAnimation);
    if(iter != zombieAnimations.end())
    {
        if(iter->second.IsFinished())
        {
            iter->second.Start();
        }
        else
        {
            zombieSprite.setTexture(*iter->second.Step(15ms));
        }
    }
    zombieSprite.setScale(-0.2f, 0.2f);
    zombieSprite.setOrigin(characterSprite.getLocalBounds().width / 2,
                           characterSprite.getLocalBounds().height / 2);

    auto& window = Context::Get<sf::RenderWindow>();
    window.draw(zombieSprite);
}


