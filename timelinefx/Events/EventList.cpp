#include "EventList.h"

namespace events
{
EventMap<void(const sf::Event::MouseButtonEvent&)> OnMousePressed;
EventMap<void(const sf::Event::KeyEvent&)> OnKeyPressed;
EventMap<void(float)> OnUpdate;
EventMap<void(sf::RenderWindow&)> OnDraw;
}
