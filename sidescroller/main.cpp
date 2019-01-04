#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <iostream>
#include <memory>
//#include <Actions/Actor.h>
#include <GameFramework/System/Random.h>
#include <GameFramework/Framework/Context.h>

int main()
{
    Random random;
    const sf::Vector2u windowSize = {1400, 900};

    sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "sidescroller");
    window.setFramerateLimit(60);

    sf::Clock clock;
    while( window.isOpen() )
    {
        window.clear(sf::Color(122, 122, 122));

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
                else
                {
//                    events::OnKeyPressed.emit(event.key);
                }
            }
        }

        int32_t deltaTime = clock.restart().asMilliseconds();
        auto deltaTimeInMS = std::chrono::milliseconds(deltaTime);

        //Actor::Details::GetActionUpdater().Update();

        window.display();
    }
}

