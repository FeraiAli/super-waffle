#pragma once
#include <Libraries/Actions/ActionDescription.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Libraries/Tweeny/TweenWrap.hpp>

namespace Core
{

struct MoveBy
{
    using Milli = std::chrono::milliseconds;

    explicit MoveBy(sf::Sprite& sprite,
                    sf::Vector2f offset,
                    Milli duration,
                    const Tween::Function& easeFunc = Tween::linear);

    MoveBy(MoveBy&& other) = default;
    MoveBy(const MoveBy& other) = default;

    MoveBy& operator=(MoveBy&& other) = default;
    MoveBy& operator=(const MoveBy& other) = default;

    Status operator()();
private:
    sf::Sprite* m_spritePtr = nullptr;
    Core::TweenWrap<sf::Vector2f> tweeny;
};

} //end of Core
