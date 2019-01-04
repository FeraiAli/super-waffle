#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Event.hpp>

#include <EventList.h>
#include <Particle.h>
#include <Libraries/Actions/ActionManager.h>

using namespace Core;
using namespace std::chrono_literals;

int main()
{
    srand(static_cast<uint32_t>(time(nullptr)));

    const sf::Vector2u windowSize = {1400, 900};
    sf::RenderWindow window(sf::VideoMode({windowSize.x, windowSize.y}), "timelinefx");
    window.setFramerateLimit(60);

    const std::string ASSET_DIR = "../timelinefx/assets/";

    fx::Init(window);
    //fx::debug::Inspect(ASSET_DIR + "explosions1/data.xml", ASSET_DIR + "explosions1/expl1_ids.txt");
    //fx::debug::Inspect(ASSET_DIR + "missles/data.xml", ASSET_DIR + "missles/missles_id.txt");
    //fx::debug::Inspect(ASSET_DIR + "shoot_em_up/data.xml", ASSET_DIR + "shoot_em_up/shoot_em_up.txt", {2, 3, 5});


    struct EmitBlast
    {
        explicit EmitBlast(float x, float y)
            : pos(x, y)
        {}

        Status operator()() const
        {
            fx::Emit(fx::Effect::Explosion_Blast1, pos);
            return Status::Finished;
        }
    private:
        sf::Vector2f pos;
    };

    int beginX = 500;
    int offset = 150;

    Sequence sequenceAction
    ({
         EmitBlast(beginX+offset,   offset), Delay(100ms),
         EmitBlast(beginX+offset*2, offset), Delay(100ms),
         EmitBlast(beginX+offset*3, offset), Delay(100ms),

         EmitBlast(beginX+offset*3, offset), Delay(100ms),
         EmitBlast(beginX+offset*3, offset*2), Delay(100ms),
         EmitBlast(beginX+offset*3, offset*3), Delay(100ms),

         EmitBlast(beginX+offset*3, offset*3), Delay(100ms),
         EmitBlast(beginX+offset*2, offset*3), Delay(100ms),
         EmitBlast(beginX+offset, offset*3), Delay(100ms),

         EmitBlast(beginX+offset, offset*3), Delay(100ms),
         EmitBlast(beginX+offset, offset*2), Delay(100ms),
         EmitBlast(beginX+offset, offset), Delay(100ms)
    });

    ActionManager actionMgr;
    actionMgr.SetAction(Repeat(sequenceAction));
    actionMgr.Start();

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
        actionMgr.Update();

        auto m = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        fx::Emit(fx::Effect::Explosion_Debrie1, m);

        float deltaTime = clock.restart().asSeconds();
        events::OnUpdate(deltaTime);

        window.clear(sf::Color(122, 122, 122));
        events::OnDraw(window);
        window.display();
    }

    fx::Deinit();
}

