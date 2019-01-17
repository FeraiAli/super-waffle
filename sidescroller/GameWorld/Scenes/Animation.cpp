#include "Animation.h"
#include "GameFramework/Entita/Pool.h"
#include "GameFramework/Framework/Context.hpp"
#include "GameFramework/Framework/ResourcesMgr.h"
#include "GameFramework/Math/RangeMap.hpp"
#include <iostream>
using namespace std::chrono_literals;

void Animation::Init(const std::vector<std::string>& animationFrames, std::chrono::milliseconds duration, bool repeatable)
{
    for(const auto& frame : animationFrames)
    {
        m_animationTextures.push_back(Context::Get<ResourcesMgr>().GetTexture(frame));
    }
    m_duration = duration;
    m_repeat = repeatable;
}

void Animation::Start()
{
    m_running = true;
    m_elapsed = 0ms;
}

bool Animation::IsFinished() const
{
    return false == m_running;
}

bool Animation::IsRepeatable() const
{
    return m_repeat;
}

const sf::Texture* Animation::Step(std::chrono::milliseconds frameTime)
{
    if(false == m_running)
    {
        return m_animationTextures.empty() ? nullptr : m_animationTextures.front();
    }

    m_elapsed += frameTime;

    if (m_elapsed >= m_duration)
    {
        m_running = false;
    }

    auto currentIndex = Math::RangeMap(m_elapsed.count(), 0l, m_duration.count(), 0ul, m_animationTextures.size() - 1);
    return m_animationTextures[currentIndex];
}

