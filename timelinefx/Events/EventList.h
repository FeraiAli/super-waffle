#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "EventMap.hpp"

namespace sf
{
    class RenderWindow;
}

namespace events
{
extern EventMap<void(const sf::Event::MouseButtonEvent&)> OnMousePressed;
extern EventMap<void(const sf::Event::KeyEvent&)> OnKeyPressed;
extern EventMap<void(float)> OnUpdate;
extern EventMap<void(sf::RenderWindow&)> OnDraw;
}
