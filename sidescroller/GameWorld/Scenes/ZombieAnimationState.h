#pragma once
#include "Animation.h"
#include "ZombieInfo.h"
#include <unordered_map>

class ZombieAnimationState
{
public:
    void Init();
    void Update();
    void Attack(bool attack);
    bool IsAttacking();
    const sf::Texture* GetTexutre();
private:
    enum class Action
    {
        Idle, Attacking
    };
    void loopAnimation(Action action);

    ZombieInfo m_info;
    Action m_action = Action::Idle;
    std::unordered_map<Action, Animation> m_animations;
    const sf::Texture* m_currentTexture = nullptr;
};
