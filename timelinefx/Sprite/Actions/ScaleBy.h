#pragma once
#include <Libraries/Actions/ActionDescription.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Libraries/Tweeny/TweenWrap.hpp>

namespace Core
{

struct ScaleBy
{
    using Milli = std::chrono::milliseconds;

    explicit ScaleBy(sf::Sprite& sprite,
                    sf::Vector2f offset,
                    Milli duration,
                    const Tween::Function& easeFunc = Tween::linear);

    ScaleBy(ScaleBy&& other) = default;
    ScaleBy(const ScaleBy& other) = default;

    ScaleBy& operator=(ScaleBy&& other) = default;
    ScaleBy& operator=(const ScaleBy& other) = default;

    Status operator()();
private:
    sf::Sprite* m_spritePtr = nullptr;
    Core::TweenWrap<sf::Vector2f> tweeny;
};

} //end of Core

