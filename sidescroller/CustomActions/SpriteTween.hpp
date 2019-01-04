#pragma once
#include <Actions/ActionDescription.h>

#include <Tweeny/Comparators.h>
#include <Tweeny/Tweeny.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <memory>

namespace SpriteAction
{

template<typename T>
struct SpriteTween
{
    explicit SpriteTween(std::shared_ptr<sf::Sprite> sprite,
                          T targetPos,
                          Action::Duration duration,
                          const Tween::Function& function = Tween::linear)
        : m_sprite(sprite)
        , m_begin({})
        , m_end(targetPos)
        , m_duration(duration)
        , m_function(function)
    {}
    virtual ~SpriteTween() = default;

    virtual void OnBegin() = 0;
    virtual void OnStep(T result) = 0;

    Action::Status operator()()
    {
        auto sprite = m_sprite.lock();
        if( sprite == nullptr)
        {
            return Action::Status::Finished;
        }

        if(m_elapsed >= m_duration)
        {
            OnStep(m_end);
            return Action::Status::Finished;
        }

        if(m_elapsed == Action::Duration::zero())
        {
            OnBegin();
        }
        m_elapsed += Action::Duration(15);

        auto progress = static_cast<float>(m_elapsed.count()) / static_cast<float>(m_duration.count());
        auto result = Tween::RangeMap(progress, 0.0f, 1.0f, m_begin, m_end, m_function);

        OnStep(result);
        return Action::Status::Running;
    }
protected:
    std::weak_ptr<sf::Sprite> m_sprite;
    T m_begin;
    T m_end;

    Action::Duration m_elapsed = Action::Duration::zero();
    Action::Duration m_duration = Action::Duration::zero();

    Tween::Function m_function = Tween::linear;
};

} //end of namespace
