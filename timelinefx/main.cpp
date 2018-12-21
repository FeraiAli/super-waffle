#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Event.hpp>

#include <EventList.h>
#include <Particle.h>

static sf::RenderWindow window;
static const sf::Vector2u windowSize = {1400, 900};

int main()
{
    srand(static_cast<uint32_t>(time(nullptr)));

    window.create(sf::VideoMode({windowSize.x, windowSize.y}), "timelinefx");
    window.setFramerateLimit(60);

    const std::string ASSET_DIR = "../timelinefx/assets/";

    fx::Init(window);
    //fx::debug::Inspect(ASSET_DIR + "explosions1/data.xml", ASSET_DIR + "explosions1/expl1_ids.txt");
    //fx::debug::Inspect(ASSET_DIR + "missles/data.xml", ASSET_DIR + "missles/missles_id.txt");
    //fx::debug::Inspect(ASSET_DIR + "shoot_em_up/data.xml", ASSET_DIR + "shoot_em_up/shoot_em_up.txt", {2, 3, 5});

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
                events::OnMousePressed.emit(event.mouseButton);
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else
                {
                    events::OnKeyPressed.emit(event.key);
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        events::OnUpdate(deltaTime);

        //fx::Emit(fx::Effect::Explosion_Blast3, {rand() % windowSize.x, rand() % windowSize.y});




















        events::OnDraw(window);
        window.display();
    }

    fx::Deinit();
}

