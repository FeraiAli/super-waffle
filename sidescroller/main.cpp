#include <SFML/Graphics.hpp>

#include <GameFramework/System/Random.h>
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/Director.h>
#include <GameFramework/System/Camera.h>
#include "GameFramework/Entita/Entity.h"
#include "GameFramework/Entita/Pool.h"
#include "GameFramework/Framework/ResourcesMgr.h"
#include <GameFramework/Math/RangeMap.hpp>

#include <GameWorld/Scenes/Scenes.h>
#include "CharacterParser/CharacterParser.h"

using namespace std::chrono_literals;

int main()
{
    auto& resMgr = Context::Add<ResourcesMgr>();
    resMgr.RegisterTexture("box", "../sidescroller/Assets/Box.png");

    auto& parser = Context::Add<Parser::CharacterParser>();
    for (auto key : parser.GetTexturePaths("knight", "idle"))    { resMgr.RegisterTexture(key, key); }
    for (auto key : parser.GetTexturePaths("knight", "run"))     { resMgr.RegisterTexture(key, key); }
    for (auto key : parser.GetTexturePaths("knight", "jump"))    { resMgr.RegisterTexture(key, key); }
    for (auto key : parser.GetTexturePaths("knight", "attack"))    { resMgr.RegisterTexture(key, key); }

    for (auto key : parser.GetTexturePaths("female_zombie", "idle"))    { resMgr.RegisterTexture(key, key); }

    auto& window = Context::Add<sf::RenderWindow>(sf::VideoMode{1600, 900}, "sidescroller");
    window.setFramerateLimit(60);

    auto& director = Context::Add<Director>();
    director.Register("game_scene", std::make_unique<GameScene>());
    director.StartWith("game_scene");
    director.InitScenes();

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
            }
        }


        int32_t deltaTime = clock.restart().asMilliseconds();
        auto deltaTimeInMS = std::chrono::milliseconds(deltaTime);

        window.clear(sf::Color(110, 200, 100));
        director.Process();
        window.display();
    }

    director.DeinitScenes();
}

