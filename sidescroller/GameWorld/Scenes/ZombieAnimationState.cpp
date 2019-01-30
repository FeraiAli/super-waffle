#include "ZombieAnimationState.h"
#include "AnimationUtilities.h"
using namespace std::chrono_literals;

void ZombieAnimationState::Init()
{
    m_animations[Action::Idle].Init(utilities::GetAnimationFrames("female_zombie", "idle"), 800ms);
    m_animations[Action::Attacking].Init(utilities::GetAnimationFrames("female_zombie", "attack"), 200ms);
}

void ZombieAnimationState::Update()
{
    if (IsAttacking())
    {
        m_currentTexture = m_animations[Action::Attacking].Step(15ms);
        return;
    }

    if(m_info.isAttacking)
    {
        loopAnimation(Action::Attacking);
    }
    else if(m_info.isIdle)
    {
        loopAnimation(Action::Idle);
    }
}

const sf::Texture *ZombieAnimationState::GetTexutre()
{
    return m_currentTexture;
}

void ZombieAnimationState::Attack(bool attack)
{
    m_info.isAttacking = attack;
}

void ZombieAnimationState::loopAnimation(ZombieAnimationState::Action action)
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
bool ZombieAnimationState::IsAttacking()
{
    auto attackAction = Action::Attacking;
    if(attackAction == m_action)
    {
        return m_animations.at(attackAction).IsRunning();
    }
    return false;
}
