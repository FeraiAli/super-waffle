#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <Libraries/Tweeny/TweenWrap.hpp>
#include <chrono>

namespace waffle
{

class Sprite : public sf::Sprite
{
public:
    Sprite();
    ~Sprite() final override;

    using Milli = std::chrono::milliseconds;

    void update(Milli dt);

    void moveBy(sf::Vector2f offset, Milli duration = Milli::zero(), Core::Tween::Function ease = Core::Tween::linear);
    void moveTo(sf::Vector2f target, Milli duration = Milli::zero(), Core::Tween::Function ease = Core::Tween::linear);

    void scaleBy(sf::Vector2f offset, Milli duration = Milli::zero(), Core::Tween::Function ease = Core::Tween::linear);
    void scaleTo(sf::Vector2f target, Milli duration = Milli::zero(), Core::Tween::Function ease = Core::Tween::linear);
private:

    //Write better tweeny - on step function required
    Core::TweenWrap<sf::Vector2f> m_tweeny;
};

} //end of namespace waffle
