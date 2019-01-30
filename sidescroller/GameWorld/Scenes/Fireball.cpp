#include "Fireball.h"
#include <GameFramework/System/Random.h>
#include "AnimationUtilities.h"
#include <iterator>
#include <cassert>
using namespace std::chrono_literals;

namespace
{
    static const int startPosX = 1100;
    static const int startPosY = 730;
    sf::Vector2f Magnitude(sf::Vector2f vec, float multiplication)
    {
        auto lenght = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
        if(lenght == 0.0f)
        {
            return sf::Vector2f();
        }

        sf::Vector2f normalized;
        normalized.x = (vec.x / lenght);
        normalized.y = (vec.y / lenght);
        return normalized * multiplication;
    }
}

void Fireball::Start(const sf::Vector2f& pos)
{
    m_alive = true;
    m_animation["red"].Init(utilities::GetAnimationFrames("fireball", "red"),   500ms);
    m_animation["pink"].Init(utilities::GetAnimationFrames("fireball", "pink"), 500ms);
    m_animation["blue"].Init(utilities::GetAnimationFrames("fireball", "blue"), 500ms);

    Random random;
    iter = m_animation.find(random({"red", "pink", "blue"}));
    m_sprite.setPosition({startPosX, startPosY});

    m_ballRect.setSize({70, 30});
    m_ballRect.setFillColor(sf::Color::White);
    m_ballRect.setPosition({startPosX , startPosY - 5});
    setDirection(pos);
}

void Fireball::Update(const sf::RectangleShape& shape)
{
    if (iter->second.IsRunning())
    {
        m_sprite.setTexture(*iter->second.Step(15ms));

        m_sprite.setScale(0.3f,0.3f);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
                           m_sprite.getLocalBounds().height / 2);
        m_sprite.move(m_velocity);
        m_ballRect.move(m_velocity);
        outOfBounds();
    }
    else
    {
        iter->second.Start();
    }

    if (interaction(shape))
    {
        m_alive = false;
    }
}

void Fireball::Draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
    window.draw(m_sprite);
}

bool Fireball::IsAlive() const
{
    return m_alive;
}

void Fireball::setDirection(const sf::Vector2f& pos)
{
    sf::Vector2f destPos;
    destPos.x = pos.x;
    destPos.y = pos.y;

    sf::Vector2f disp;
    disp.x = destPos.x - m_startingPos.x;
    disp.y = destPos.y - m_startingPos.y;
    sf::Vector2f distance;
    distance.x = std::hypot(disp.x, disp.y);
    distance.y = std::hypot(disp.y, disp.x);

    m_velocity.x = disp.x * (m_speed / distance.x);
    m_velocity.y = disp.y * (m_speed / distance.y);

    double dx = double(destPos.x - 1100);
    double dy = double(destPos.y - 730);
    float angle = float(atan2(dy, dx) * 180 / M_PI - 180);
    m_sprite.setRotation(angle);

    const sf::Vector2f nextPos = m_sprite.getPosition() - m_velocity;
    const sf::Vector2f dir = Magnitude((m_sprite.getPosition() - nextPos), 80.0f);
    m_ballRect.setRotation(angle);
    m_ballRect.move(dir);
}

void Fireball::outOfBounds()
{
    auto posX = m_sprite.getPosition().x;
    auto posY = m_sprite.getPosition().y;
    auto rect = m_sprite.getGlobalBounds();

    if ((posX + (rect.width / 2)) < 0 or (posX - (rect.width / 2)) > 1600)
    {
        m_alive = false;
    }
    if ((posY + rect.height / 2) < 0 or (posY - rect.height/ 2) > 900)
    {
        m_alive = false;
    }
}

bool Fireball::interaction(const sf::RectangleShape &shape)
{
    return (m_ballRect.getGlobalBounds().intersects(shape.getGlobalBounds()));
}

