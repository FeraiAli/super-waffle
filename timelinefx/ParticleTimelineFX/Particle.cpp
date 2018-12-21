#include "Particle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <DataParser/TLFXEffect.h>
#include "EffectLibrary.h"
#include "ParticleManager.h"
#include "EventList.h"

#include <unordered_map>
#include <fstream>

namespace fx
{

static ParticleManager particleManager;
static EffectLibrary   effectLibrary;

static const std::unordered_map<Effect, std::string> particleIdMap =
{
     {Effect::Explosion_Blast1, "32 Frames/Cloud Blast 2"}
    ,{Effect::Explosion_Blast2, "32 Frames/Cloud Blast 3"}
    ,{Effect::Explosion_Blast3, "32 Frames/Cloud Blast 4"}
    ,{Effect::Explosion_Blast4, "32 Frames/Cloud Blast 5"}

    ,{Effect::Explosion_Cloud1, "64 Frames/Cloud Explosion 3"}
    ,{Effect::Explosion_Cloud2, "48 Frames/Cloud Explosion 6"}
    ,{Effect::Explosion_Cloud3, "64 Frames/Cloud Explosion 7"}

    ,{Effect::Explosion_Debrie1, "64 Frames/Debrie Explosion 4"}
};

void _emit(const std::string& effectName, sf::Vector2f pos, float scale = 1.0f)
{
    if(effectName.empty())
    {
        return;
    }

    auto prototypeEffect = effectLibrary.GetEffect(effectName.c_str());
    if(prototypeEffect == nullptr)
    {
        return;
    }

    auto copyEffect = new TLFX::Effect(*prototypeEffect, &particleManager);
    copyEffect->SetPosition(pos.x, pos.y);
    copyEffect->SetScaleX(scale);
    copyEffect->SetScaleY(scale);
    particleManager.AddEffect(copyEffect);
}

void Emit(Effect effect, sf::Vector2f pos, float scale)
{
    const auto effectName = particleIdMap.at(effect);
    _emit(effectName, pos, scale);
}

void Init(sf::RenderWindow &window)
{
    events::OnUpdate.connect([&](float)
    {
        particleManager.Update();
    });

    events::OnDraw.connect([&](sf::RenderWindow&)
    {
        particleManager.DrawParticles();
        particleManager.Flush();
    });

    effectLibrary.Load("../timelinefx/assets/explosions1/data.xml");

    const int width =  static_cast<int>(window.getSize().x);
    const int height = static_cast<int>(window.getSize().y);

    particleManager.SetRenderWindow(&window);
    particleManager.SetScreenSize(width, height);
    particleManager.SetOrigin(width / 2, height / 2);
    particleManager.SetIdleTimeLimit(30);
    particleManager.SetGlobalAmountScale(0.15f);
}

void Deinit()
{
    particleManager.Destroy();
}

namespace debug
{

struct Inspector
{
    using EffectList = std::vector<std::string>;

    explicit Inspector(const EffectList& efList, std::vector<int> ignoreIndecies)
        : m_effectNames(efList)
        , m_currentEffect(m_effectNames.begin())
    {
        for(auto i : ignoreIndecies)
        {
            m_effectNames[static_cast<size_t>(i)] = "";
        }
    }

    void draw(sf::RenderWindow& window)
    {
        drawText(window, "Use 'Q' and 'W' to navigate between effects.", {10, 10});
        drawText(window, "Use 'E' to save effect name into 'outputDir'", {10, 50});
        drawText(window, "Current effect name: " + current(), {10, 90});
        drawText(window, "Current effect id: " + std::to_string((m_currentEffect - m_effectNames.begin())), {10, 130});
    }

    void next()
    {
        if(m_currentEffect != m_effectNames.cend() - 1) { m_currentEffect++; }
    }

    void prev()
    {
        if(m_currentEffect != m_effectNames.cbegin()) { m_currentEffect--; }
    }

    std::string current() const
    {
        return *m_currentEffect;
    }

private:
    void drawText(sf::RenderWindow& window, const std::string& message, sf::Vector2f pos)
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

    sf::Vector2f m_pos;
    EffectList m_effectNames;
    EffectList::const_iterator m_currentEffect;
};

void Inspect(const std::string& dataFileName, const std::string& outputDir, std::vector<int> ignoreIndecies)
{
    effectLibrary.Load(dataFileName.c_str());
    static Inspector inspector(effectLibrary.GetAllEffectsName(), ignoreIndecies);

    events::OnKeyPressed.connect([&](const sf::Event::KeyEvent& key)
    {
        if(key.code == sf::Keyboard::Q) { inspector.prev(); }
        if(key.code == sf::Keyboard::W) { inspector.next(); }
        if(key.code == sf::Keyboard::E)
        {
            std::fstream file(outputDir, std::ios::app);
            file << inspector.current() << '\n';
        }
    });

    srand(153);
    events::OnDraw.connect([&](sf::RenderWindow& window)
    {
        static int i = 0;
        if(i % 25 == 0)
        {
            _emit(inspector.current(), {static_cast<float>(window.getSize().x / 2 + (rand() % 50)),
                                        static_cast<float>(window.getSize().y / 2 + (rand() % 50))});
        }
        i++;

        inspector.draw(window);
    });
}

} //end of debug
} //end of fx

