#include "GameScene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <GameFramework/Framework/Context.hpp>
#include "../Components/Components.h"
#include "../Systems/Systems.h"
#include "GameWorld/EntityFactory/EntityFactory.h"

#include "GameEditorScene.h"

void GameScene::Init()
{
    auto& pool = Context::Add<Entita::Pool>();

    pool.RegisterSystem<DrawSystem>();
    pool.RegisterSystem<MoveSystem>();
    pool.RegisterSystem<CollisionSystem>();
    pool.RegisterSystem<AIControlSystem>();
    pool.RegisterSystem<EnemySpawnSystem>();
    pool.RegisterSystem<AttackSystem>();
    pool.RegisterSystem<AnimationSystem>();

    EntityFactory::CreatePlayer1({750, 20});
//    EntityFactory::CreatePlayer2({750, 50});
}

void GameScene::Show()
{
    auto& pool = Context::Get<Entita::Pool>();
    auto stringMap = GameEditorScene::GetStringMap();

//    for(auto& player : pool.GetEntities<Player>())
//    {
//        player->GetComponent<Body>().setPosition(750, 20);
//    }

//    for(auto& enemy : pool.GetEntities<Enemy>())
//    {
//        auto& body = enemy->GetComponent<Body>();
//        body.size = EntitySettings::Size;
//        body.velocity.x = -7.0f;
//        body.setPosition(850, 20);
//    }

    for(size_t y = 0; y < stringMap.size(); y++)
    {
        for(size_t x = 0; x < stringMap[y].size(); x++)
        {
            if(stringMap[y][x] == '#')
            {
                sf::Vector2f pos = {(x * EntitySettings::Size.x),
                                    (y * EntitySettings::Size.y)};
                EntityFactory::CreateTile(pos);
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

//    auto enemies = pool.GetEntities<Enemy>();
//    for(auto enemy : enemies)
//    {
//        pool.RemoveEntity(enemy);
//    }
}

void GameScene::Process()
{
    auto& pool = Context::Get<Entita::Pool>();
    pool.Process();
}
