#include "Camera.h"
#include "Random.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Math/RangeMap.hpp"

namespace Settings
{
    const float MaxAngle = 10.0f;
    const float MaxOffset = 10.0f;
    const float TraumaDecreaseFactor = 0.035f;
//    const float FollowSpeedFactor = 0.05f;
}


Camera::Camera(sf::RenderWindow &window)
    : m_window(window)
{
    m_view.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
    m_view.setSize(m_window.getSize().x, m_window.getSize().y);
}

//void Camera::follow(sf::Vector2f target)
//{
//    float moveX = ((0.9f * target.x) + (0.1f * target.x)) * Settings::FollowSpeedFactor;
//    float moveY = ((0.9f * target.y) + (0.1f * target.y)) * Settings::FollowSpeedFactor;
//    m_view.move(moveX, moveY);
//}

void Camera::update()
{
    if(m_traumaFactor == 0.0f)
    {
        m_window.setView(m_window.getDefaultView());
    }
    else
    {
        m_traumaFactor = std::max(m_traumaFactor - Settings::TraumaDecreaseFactor, 0.0f);
        auto shakeFactor = m_traumaFactor * m_traumaFactor;

        Random random;
        float angle = Settings::MaxAngle * shakeFactor * random(-1.0f, 1.0f);
        float offsetX = Settings::MaxOffset * shakeFactor * random(-1.0f, 1.0f);
        float offsetY = Settings::MaxOffset * shakeFactor * random(-1.0f, 1.0f);

        if(m_traumaFactor < 0.25f)
        {
            angle = Math::RangeMap(m_traumaFactor, 0.25f, 0.0f, angle, 0.0f);

            float targetX = -m_view.getViewport().left;
            float targetY = -m_view.getViewport().top;
            offsetX = Math::RangeMap(m_traumaFactor, 0.25f, 0.0f, offsetX, targetX);
            offsetY = Math::RangeMap(m_traumaFactor, 0.25f, 0.0f, offsetY, targetY);
        }

        m_view.setRotation(angle);
        m_view.move(offsetX, offsetY);
        m_window.setView(m_view);
    }
}

void Camera::shake(float factor)
{
    m_traumaFactor = std::min(m_traumaFactor + factor, 1.0f);
}
