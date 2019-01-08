#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <iostream>
#include <memory>

#include <GameFramework/System/Random.h>
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/Director.h>
#include <GameFramework/System/Camera.h>

#include "TileMap/Editor/TileEditor.h"
#include "TileMap/Map/TileMap.h"

int main()
{
    auto& window = Context::Add<sf::RenderWindow>(sf::VideoMode{1400, 900}, "sidescroller");
    window.setFramerateLimit(60);

    auto& director = Context::Add<Director>();
    director.Register("tile_map_editor", std::make_unique<TileEditor>());
    director.Register("tile_map", std::make_unique<TileMap>());
    director.StartWith("tile_map");
    director.InitScenes();

    const std::vector<sf::RectangleShape> background = [&]()
    {
        bool b = false;
        std::vector<sf::RectangleShape> bgr;
        for(int i = 0; i < window.getSize().x; i+=50)
        {
            b = !b;
            for(int j = 0; j < window.getSize().y; j+=50)
            {
                sf::RectangleShape rect;
                rect.setFillColor((b = !b) ? sf::Color::White : sf::Color::Green);
                rect.setPosition(i, j);
                rect.setSize({50, 50});
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(1.0f);
                bgr.push_back(rect);
            }
        }
        return bgr;
    }();

    auto& camera = Context::Add<Camera>(window);

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
                    director.Change("tile_map");
                }
                else if(event.key.code == sf::Keyboard::F2)
                {
                    director.Change("tile_map_editor");
                }
            }
        }

        int32_t deltaTime = clock.restart().asMilliseconds();
        auto deltaTimeInMS = std::chrono::milliseconds(deltaTime);

//        camera.update();

        window.clear(sf::Color::White);
        director.Process();
        window.display();
    }
}

