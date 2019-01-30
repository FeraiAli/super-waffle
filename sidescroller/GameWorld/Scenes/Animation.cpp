#include "Animation.h"
#include "GameFramework/Entita/Pool.h"
#include "GameFramework/Framework/Context.hpp"
#include "GameFramework/Framework/ResourcesMgr.h"
#include "GameFramework/Math/RangeMap.hpp"
#include <iostream>
using namespace std::chrono_literals;

Animation::Animation(const std::vector<std::string> &animationFrames, std::chrono::milliseconds duration)
{
    Init(animationFrames, duration);
}

void Animation::Init(const std::vector<std::string>& animationFrames, std::chrono::milliseconds duration)
{
    for(const auto& frame : animationFrames)
    {
        m_animationTextures.push_back(Context::Get<ResourcesMgr>().GetTexture(frame));
    }
    m_duration = duration;
}

void Animation::Start()
{
    m_running = true;
    m_elapsed = 0ms;
}

void Animation::Stop()
{
    m_running = false;
    m_elapsed = 0ms;
}

bool Animation::IsRunning() const
{
    return m_running;
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

