#include "KnightAnimationState.h"
#include "AnimationUtilities.h"
using namespace std::chrono_literals;

void KnightAnimationState::Init()
{
    m_animations[Action::Idle].Init(utilities::GetAnimationFrames("knight", "idle"), 600ms);
    m_animations[Action::Running].Init(utilities::GetAnimationFrames("knight", "run"), 500ms);
    m_animations[Action::Attacking].Init(utilities::GetAnimationFrames("knight", "attack"), 400ms);
}

void KnightAnimationState::Update(const CharacterInfo& characterInfo)
{
    if(IsAttacking())
    {
        m_currentTexture = m_animations.at(Action::Attacking).Step(15ms);
        return;
    }

    if(characterInfo.isAttacking)
    {
        m_animations.at(Action::Attacking).Start();
        m_action = Action::Attacking;
    }
    else if(characterInfo.isMoving)
    {
        loopAnimation(Action::Running);
    }
    else
    {
        loopAnimation(Action::Idle);
    }
}

const sf::Texture *KnightAnimationState::GetTexture()
{
    return m_currentTexture;
}

bool KnightAnimationState::IsAttacking()
{
    auto attackAction = Action::Attacking;
    if(attackAction == m_action)
    {
        return m_animations.at(attackAction).IsRunning();
    }
    return false;
}

void KnightAnimationState::loopAnimation(KnightAnimationState::Action action)
{
    auto& anim = m_animations.at(action);

    if(action == m_action)
    {
        if(false == anim.IsRunning())
        {
            anim.Start();
        }
    }
    else
    {
        anim.Start();
    }

    m_currentTexture = anim.Step(15ms);
    m_action = action;
}
