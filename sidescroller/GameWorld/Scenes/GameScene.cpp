#include "GameScene.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>
#include <SFML/Window/Event.hpp>


void GameScene::Init()
{
    //std::vector<std::vector<std::vector<std::vector<int>>>> FourInts;
    //FourInts.resize(10, std::vector<std::vector<std::vector<int>>>(10, std::vector<std::vector<int>>(10, std::vector<int>(10, 100))));
    m_map.Init();
}

void GameScene::Deinit()
{
    m_map.SaveMap();
}

void GameScene::Process()
{
    m_map.Process(Context::Get<sf::RenderWindow>());
}


