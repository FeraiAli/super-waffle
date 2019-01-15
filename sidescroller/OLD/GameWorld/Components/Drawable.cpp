#include "Drawable.h"
#include <GameFramework/Framework/Context.hpp>
#include <GameFramework/Framework/ResourcesMgr.h>

void Drawable::AddAnimations(std::string characterAnimation, std::vector<std::string> framesContainer, std::chrono::milliseconds animationDuration)
{
    m_animations[characterAnimation].frames = framesContainer;
    m_animations[characterAnimation].duration = animationDuration;
}

bool Drawable::HasAnimation() const
{
    return m_currentAnim != m_animations.end();
}

bool Drawable::SetAnimation(std::string characterAnimation)
{
    auto iter = m_animations.find(characterAnimation);
    if(iter != m_animations.end())
    {
        m_currentAnim = iter;
        m_currentAnim->second.elapsed = std::chrono::milliseconds::zero();
        return true;
    }
    return false;
}

std::map<std::string, Drawable::Animation>::iterator Drawable::GetCurrentAnimation()
{
    return m_currentAnim;
}
