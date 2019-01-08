#pragma once
#include <SFML/Graphics/View.hpp>

namespace sf
{
    class RenderWindow;
}

class Camera
{
public:
    explicit Camera(sf::RenderWindow& window);

//TODO - follow will be done, when needed
//    void follow(sf::Vector2f target);
    void shake(float factor = 0.35f);

    void update();
private:
    float m_traumaFactor = 0.0f;
    sf::View m_view;
    sf::View m_defaultView;
    sf::RenderWindow& m_window;
};
