#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>

#include <SFML/Window/Event.hpp>
#include <timelinefx_sfml/ParticleManager.h>
#include <timelinefx_sfml/EffectLibrary.h>
#include <timelinefx_parser/TLFXEffect.h>
#include <core/event.hpp>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <experimental/optional>

static EffectLibrary effectLibrary;
static ParticleManager particleMgr;
static sf::RenderWindow window;
static const sf::Vector2u windowSize = {1400, 900};
static core::event<void(const std::string&)> EmitParticle;

void DrawText(const std::string& message, sf::Vector2f pos)
{
    static const sf::Font font = []()
    {
        sf::Font localFont;
        localFont.loadFromFile("../timelinefx/assets/arialnb.ttf");
        return localFont;
    }();

    sf::Text text;
    text.setFont(font);
    text.setPosition(pos);
    text.setString(message);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1.0f);
    text.setOutlineColor(sf::Color::Blue);
    text.setScale(0.6f, 0.6f);

    const int spacing = 10;
    sf::RectangleShape textBackground;
    textBackground.setPosition(text.getPosition().x - spacing,
                               text.getPosition().y - spacing );

    textBackground.setSize({text.getGlobalBounds().width + (spacing * 2),
                            text.getGlobalBounds().height + (spacing * 2)});
    textBackground.setFillColor(sf::Color::Black);

    window.draw(textBackground);
    window.draw(text);
}

template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
void DrawText(T message, sf::Vector2f pos)
{
    DrawText(std::to_string(message), pos);
}

void startEffect(const std::string& effectName,
                 std::experimental::optional<sf::Vector2f> posOptional = std::experimental::nullopt)
{
    static const int EFFECT_COUNT = 2;

    auto prototypeEffect = effectLibrary.GetEffect(effectName.c_str());
    if(prototypeEffect == nullptr)
    {
        return;
    }

    for(int i = 0; i < EFFECT_COUNT; i++)
    {
        sf::Vector2f pos;
        if(posOptional == std::experimental::nullopt)
        {
            pos.x = rand() % windowSize.x;
            pos.y = rand() % windowSize.y;
        }
        else
        {
            pos = posOptional.value();
        }

        auto copyEffect = new TLFX::Effect(*prototypeEffect, &particleMgr);
        copyEffect->SetPosition(pos.x, pos.y);
//        copyEffect->SetLife(4.4f);
//        copyEffect->SetAmount(1.5f);
//        copyEffect->SetVelocity(0.5f);
        particleMgr.AddEffect(copyEffect);
    }
}

int main()
{
    srand(static_cast<uint32_t>(time(nullptr)));

    window.create(sf::VideoMode({windowSize.x, windowSize.y}), "timelinefx");
    window.setFramerateLimit(60);

    effectLibrary.Load("../timelinefx/assets/explosions1/data.xml");
//    effectLibrary.Load("../timelinefx/assets/missles/data.xml");
//    effectLibrary.Load("../timelinefx/assets/shoot_em_up/data.xml");

    particleMgr.SetRenderWindow(&window);
    particleMgr.SetScreenSize(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
    particleMgr.SetOrigin(windowSize.x / 2, windowSize.y / 2);
    particleMgr.SetIdleTimeLimit(30);
    particleMgr.SetGlobalAmountScale(0.15f);

    EmitParticle.connect([&](const std::string& name)
    {
        startEffect(name, std::experimental::nullopt);
    });

    std::vector<std::string> supportedEffectList;
    std::ifstream explosionListFile("../timelinefx/assets/explosions1/explosion_ids.txt");
    std::string line;
    while ( std::getline(explosionListFile, line) )
    {
        supportedEffectList.push_back(line);
    }

//    supportedEffectList = effectLibrary.GetAllEffectsName();

    std::vector<std::string>::const_iterator selectedEffect = supportedEffectList.cbegin();

    sf::Clock clock;
    float minFPS = 999999.0f;
    size_t framePassed = 0;
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
                if(event.mouseButton.button == sf::Mouse::Left)
                {
//                    startEffect(*selectedEffect);
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
//                    std::ofstream file("../timelinefx/assets/explosions1/explosion_ids.txt", std::ios::app);
//                    file << *selectedEffect << std::endl;
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::W)
                {
                    if(selectedEffect != supportedEffectList.cend() - 1) { selectedEffect++; }
                }
                else if(event.key.code == sf::Keyboard::Q)
                {
                    if(selectedEffect != supportedEffectList.cbegin()) { selectedEffect--; }
                }
                else if(event.key.code == sf::Keyboard::Space)
                {

                }
            }
        }
        if(framePassed % 1 == 0)
        {
            EmitParticle.emit(*selectedEffect);
        }

        particleMgr.Update();
        particleMgr.DrawParticles();
        particleMgr.Flush();

        auto currentFPS = (1.0f / clock.restart().asSeconds());
        minFPS = std::min(currentFPS, minFPS);

        DrawText("Effect Name: " + *selectedEffect, {10, 10});
        DrawText("FPS: " + std::to_string(currentFPS), {10, 40});
        DrawText("Min FPS: " + std::to_string(minFPS), {10, 70});
        DrawText("Particle Count: " + std::to_string(particleMgr.GetParticlesInUse()), {10, 100});

        window.display();
        framePassed++;
    }

    particleMgr.Destroy();
}
