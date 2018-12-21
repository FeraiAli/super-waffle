#pragma once
#include <chrono>
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include "Easing.h"
#include "RangeMap.hpp"

using namespace std::chrono_literals;
namespace Core
{
template<typename T>
class TweenWrap
{
public:
    using Milli = std::chrono::milliseconds;
    using OnEndCallback = std::function<void(TweenWrap<T>&)>;

    struct TargetPoint
    {
        T target;
        Milli duration = Milli::zero();
        Tween::Function easing;

        OnEndCallback onEnd;
        bool onEndDispatched = false;
    };

    TweenWrap<T>& AddTarget(const T& target)
    {
        TargetPoint targetPoint;
        targetPoint.target = target;
        m_targets.emplace_back(std::move(targetPoint));

        return *this;
    }

    TweenWrap<T>& During(Milli duration)
    {
        auto secondTargetPoint = std::next(m_targets.begin(), 1);
        if(secondTargetPoint == m_targets.end())
        {
            return *this;
        }

        auto targetWithDuration = std::find_if(secondTargetPoint, m_targets.end(), [](const auto& targetPoint)
        {
            return targetPoint.duration == Milli::zero();
        });

        bool allTargetsHasDuration = (targetWithDuration == m_targets.end());
        if(allTargetsHasDuration)
        {
            auto oldDuration = m_targets.back().duration;
            m_duration -= oldDuration;
            m_duration += duration;
            m_elapsed = m_duration;

            m_targets.back().duration = duration;
            return *this;
        }

        m_duration += duration;
        m_elapsed = m_duration;

        auto notSetCount = std::distance(targetWithDuration, m_targets.end());
        auto averageDuration = (duration / notSetCount);
        for(auto it = targetWithDuration; it != m_targets.end(); ++it)
        {
            it->duration = averageDuration;
        }
        return *this;
    }

    TweenWrap<T>& Via(const Tween::Function& easing)
    {
        m_targets.back().easing = easing;
        return *this;
    }

    TweenWrap<T>& OnEnd(const OnEndCallback& onEnd)
    {
        m_targets.back().onEnd = onEnd;
        return *this;
    }

    void Start()
    {
        if(m_targets.empty())
        {
            std::cerr << "{Warning} TweenWrap::Start() ignored, missing target points!" << std::endl;
            return;
        }

        m_elapsed = Milli::zero();
        m_currentTarget = m_targets.front().target;
        m_prevTarget = m_currentTarget;

        m_running = true;
        for(auto& target : m_targets)
        {
            target.onEndDispatched = false;
        }
    }

    void Stop()
    {
        m_running = false;
    }

    void Update(Milli dt)
    {
        if(false == m_running)
        {
            return;
        }

        if(m_elapsed >= m_duration)
        {
            m_running = false;
            dispatchOnEnd(m_targets.back());
            m_prevTarget = m_currentTarget;
        }
        else
        {
            m_elapsed += dt;
            m_elapsed = std::min(m_elapsed, m_duration);
            m_prevTarget = m_currentTarget;
            seekTo(m_elapsed);
        }
    }

    T GetDelta() const
    {
        return m_currentTarget - m_prevTarget;
    }

    const T& Get() const
    {
        return m_currentTarget;
    }

    bool IsRunning() const
    {
        return m_running;
    }

    void Clear()
    {
        m_running = false;

        m_prevTarget = {};
        m_currentTarget = {};
        m_targets.clear();

        m_elapsed = Milli::zero();
        m_duration = Milli::zero();
    }
private:
    void seekTo(Milli timePoint)
    {
        Milli pastTime = 0ms;
        size_t curIdx = 0;
        for(size_t i = 1; i < m_targets.size() - 1; i++)
        {
            const auto& targetPoint = m_targets[i];
            auto nextPastTime = targetPoint.duration;
            if((timePoint >= pastTime) && (timePoint <= (pastTime + nextPastTime)))
            {
                break;
            }
            pastTime += nextPastTime;
            curIdx++;
        }
        size_t nextIdx = std::min(curIdx + 1, m_targets.size() - 1);

        ///Find if any user set easing from curIdx ahead.
        Tween::Function easingFunction = [&]()->std::function<double(double)>
        {
            auto hasEasingComp = [](const auto& cp) { return cp.easing != nullptr; };
            auto easeEndIt = std::find_if(m_targets.begin() + nextIdx, m_targets.end(), hasEasingComp);
            //auto easeBeginIt = std::find_if(m_targets.begin(), easeEndIt, hasEasingComp);

            return (easeEndIt == m_targets.end()) ? Tween::linear : easeEndIt->easing;
        }();

        auto elapsed = timePoint - pastTime;
        m_currentTarget = Tween::RangeMap(elapsed,
                                          0ms,
                                          m_targets[nextIdx].duration,
                                          m_targets[curIdx].target,
                                          m_targets[nextIdx].target,
                                          easingFunction);

        dispatchOnEnd(m_targets[curIdx]);
    }

private:
    void dispatchOnEnd(TargetPoint& target)
    {
        if((nullptr != target.onEnd) && (target.onEndDispatched == false))
        {
            target.onEndDispatched = true;
            target.onEnd(*this);
        }
    }

private:
    bool m_running = false;

    T m_prevTarget;
    T m_currentTarget;
    std::vector<TargetPoint> m_targets;

    Milli m_elapsed = Milli::zero();
    Milli m_duration = Milli::zero();
};

} //end of Core
