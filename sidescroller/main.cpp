#include <SFML/Graphics.hpp>

#include <GameFramework/System/Random.h>
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/Director.h>
#include <GameFramework/System/Camera.h>
#include "GameFramework/Entita/Entity.h"
#include "GameFramework/Entita/Pool.h"

#include <GameWorld/Systems/Systems.h>
#include <GameWorld/Components/Components.h>
#include <GameWorld/Scenes/Scenes.h>

#include <PhysicsBox2D/Box2DWorld.h>
#include <GameFramework/Math/RangeMap.hpp>
using namespace std::chrono_literals;

int main()
{
    Context::Add<Box2DWorld>();

    auto& window = Context::Add<sf::RenderWindow>(sf::VideoMode{1400, 900}, "sidescroller");
    window.setFramerateLimit(60);

    auto& director = Context::Add<Director>();
    director.Register("game_editor_scene", std::make_unique<GameEditorScene>());
    director.Register("game_scene", std::make_unique<GameScene>());
    director.StartWith("game_scene");
    director.InitScenes();

    //float res = Math::RangeMap(100ms, 0ms, 200ms, 1.0f, 2.0f);

    sf::Clock clock;
    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent(event) )
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
//                events::OnMousePressed.emit(event.mouseButton);
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if(event.key.code == sf::Keyboard::F1)
                {
                    director.Change("game_scene");
                }
                else if(event.key.code == sf::Keyboard::F2)
                {
                    director.Change("game_editor_scene");
                }
            }
        }

        int32_t deltaTime = clock.restart().asMilliseconds();
        auto deltaTimeInMS = std::chrono::milliseconds(deltaTime);

        window.clear(sf::Color::White);
        director.Process();
        window.display();
    }

    director.DeinitScenes();
}

