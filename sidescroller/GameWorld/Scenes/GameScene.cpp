#include "GameScene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include "../Components/Components.h"
#include "../Systems/Systems.h"

#include "GameEditorScene.h"

void GameScene::Init()
{
    auto& pool = Context::Add<Entita::Pool>();

    pool.RegisterSystem<DrawSystem>();
    pool.RegisterSystem<MoveSystem>();
    pool.RegisterSystem<CollisionSystem>();

    auto player = pool.CreateEntity();
    player->AddComponent<Movable>();
    player->AddComponent<Jumpable>();
    player->AddComponent<Collidable>();
    player->AddComponent<WASDController>();
    player->AddComponent<Agent>();

    auto& skin = player->AddComponent<Skin>();
    skin.setFillColor(sf::Color::Green);

    auto& body = player->AddComponent<Body>();
    body.size = {25, 50};
    body.setPosition(725, 50);
}

void GameScene::Show()
{
    auto& pool = Context::Get<Entita::Pool>();

    //DEBUG - Player1 Begin Pos
    auto player1 = pool.GetSingleEntity<WASDController>();
    player1->GetComponent<Body>().setPosition(725, 50);

    auto stringMap = GameEditorScene::GetStringMap();
    const auto windowSize = Context::Get<sf::RenderWindow>().getSize();
    sf::Vector2f tileSize;
    tileSize.x = windowSize.x / GameEditorScene::GetTilesCount().x;
    tileSize.y = windowSize.y / GameEditorScene::GetTilesCount().y;

    for(size_t y = 0; y < stringMap.size(); y++)
    {
        for(size_t x = 0; x < stringMap[y].size(); x++)
        {
            if(stringMap[y][x] == '#')
            {
                sf::Vector2f pos = {(x * tileSize.x), (y * tileSize.y)};

                auto entity = pool.CreateEntity();
                entity->AddComponent<Tile>();
                entity->AddComponent<Collidable>();

                auto& skin = entity->AddComponent<Skin>();
                skin.setPosition(pos);
                skin.setSize(tileSize);
                skin.setFillColor(GameEditorScene::SolidColor);

                auto& body = entity->AddComponent<Body>();
                body.setPosition(pos);
                body.size = tileSize;
            }
        }
    }
}

void GameScene::Hide()
{
    auto& pool = Context::Get<Entita::Pool>();
    auto entities = pool.GetEntities<Tile>();
    for(auto entity : entities)
    {
        pool.RemoveEntity(entity);
    }
}

void GameScene::Process()
{
    auto& pool = Context::Get<Entita::Pool>();
    pool.Process();
}
