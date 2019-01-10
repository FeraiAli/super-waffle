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

    auto& body = player->AddComponent<Body>(sf::Vector2f(25, 50), Body::Type::Dynamic);
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
        sf::FloatRect tileBox;
        bool tileBoxInited = false;
        for(size_t x = 0; x < stringMap[y].size(); x++)
        {       
            bool isSolid = stringMap[y][x] == '#';
            if(isSolid)
            {
                if(tileBoxInited)
                {
                    tileBox.width += tileSize.x;
                }
                else
                {
                    tileBoxInited = true;
                    tileBox.left = x * tileSize.x;
                    tileBox.top = y * tileSize.y;
                    tileBox.width = tileSize.x;
                    tileBox.height = tileSize.y;
                }
            }

            bool isLastIteration = (x == stringMap[y].size() - 1);
            if(tileBoxInited and (isLastIteration or (not isSolid)))
            {
                auto entity = pool.CreateEntity();
                entity->AddComponent<Tile>();
                entity->AddComponent<Collidable>();

                auto& skin = entity->AddComponent<Skin>();
                skin.setOutlineColor(sf::Color::Black);
                skin.setFillColor(GameEditorScene::SolidColor);

                auto& body = entity->AddComponent<Body>(sf::Vector2f(tileBox.width, tileBox.height), Body::Type::Static);
                body.setPosition({tileBox.left, tileBox.top});

                tileBox = sf::FloatRect();
                tileBoxInited = false;
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
