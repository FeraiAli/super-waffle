#pragma once
#include "Easing.h"
#include "RangeMap.hpp"
#include <functional>
#include <vector>
#include <chrono>

template<typename T>
class Tweeny
{
public:
    using Milli = std::chrono::milliseconds;

    Tweeny() = default;
    explicit Tweeny(T begin, T end, Milli duration, const Tween::Function& function = Tween::linear);

    void Start();
    void Stop();

    T Step(Milli dt);
    bool IsFinished() const;
private:
    bool m_running = false;
    T m_begin;
    T m_end;

    Milli m_elapsed = Milli::zero();
    Milli m_duration = Milli::zero();

    Tween::Function m_function = Tween::linear;
};

template<typename T>
Tweeny<T>::Tweeny(T begin, T end, Tweeny<T>::Milli duration, const Tween::Function& function)
    : m_begin(begin)
    , m_end(end)
    , m_duration(duration)
    , m_function(function)
{}

template<typename T>
void Tweeny<T>::Start()
{
    if(m_begin == m_end)
    {
        return;
    }

    m_elapsed = Tweeny<T>::Milli::zero();
    m_running = true;
}

template<typename T>
void Tweeny<T>::Stop()
{
    m_running = false;
}

template<typename T>
T Tweeny<T>::Step(Tweeny<T>::Milli dt)
{
    if(IsFinished())
    {
        return m_end;
    }

    m_elapsed += dt;
    if(m_elapsed >= m_duration)
    {
        m_running = false;
        return m_end;
    }
    else
    {
        float progress = static_cast<float>(m_elapsed.count()) / static_cast<float>(m_duration.count());
        T result = Tween::RangeMap(progress, 0.0f, 1.0f, m_begin, m_end, m_function);
        return result;
    }
}

template<typename T>
bool Tweeny<T>::IsFinished() const
{
    return (false == m_running);
}
