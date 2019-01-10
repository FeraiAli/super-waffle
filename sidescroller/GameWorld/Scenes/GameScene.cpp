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
    pool.RegisterSystem<AIControlSystem>();
    pool.RegisterSystem<EnemySpawnSystem>();

    auto createPlayer = [&](sf::Color color)
    {
        auto player = pool.CreateEntity();
        player->AddComponent<Movable>();
        player->AddComponent<Jumpable>();
        player->AddComponent<Collidable>();
        player->AddComponent<Player>();
        player->AddComponent<Body>();
        auto& skin = player->AddComponent<Skin>();
        skin.setFillColor(color);
        return player;
    };
    auto player1 = createPlayer(sf::Color::Green);
    player1->AddComponent<WASDController>();

    auto player2 = createPlayer(sf::Color::Magenta);
    player2->AddComponent<ArrowController>();
}

void GameScene::Show()
{
    auto& pool = Context::Get<Entita::Pool>();

    auto stringMap = GameEditorScene::GetStringMap();
    const auto windowSize = Context::Get<sf::RenderWindow>().getSize();
    sf::Vector2f tileSize;
    tileSize.x = windowSize.x / GameEditorScene::GetTilesCount().x;
    tileSize.y = windowSize.y / GameEditorScene::GetTilesCount().y;

    for(auto& player : pool.GetEntities<Player>())
    {
        auto& body = player->GetComponent<Body>();
        body.size = tileSize;
        body.setPosition(750, 20);
    }

    for(auto& enemy : pool.GetEntities<Enemy>())
    {
        auto& body = enemy->GetComponent<Body>();
        body.size = tileSize;
        body.velocity.x = -7.0f;
        body.setPosition(850, 20);
    }

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

    auto tiles = pool.GetEntities<Tile>();
    for(auto tile : tiles)
    {
        pool.RemoveEntity(tile);
    }

    auto enemies = pool.GetEntities<Enemy>();
    for(auto enemy : enemies)
    {
        pool.RemoveEntity(enemy);
    }
}

void GameScene::Process()
{
    auto& pool = Context::Get<Entita::Pool>();
    pool.Process();
}
