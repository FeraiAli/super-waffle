#pragma once
#include "Animation.h"
#include "CharacterInfo.h"
#include <unordered_map>

class KnightAnimationState
{
public:
    void Init();

    void Update(const CharacterInfo& characterInfo);
    const sf::Texture* GetTexture();
    bool IsAttacking();
private:
    enum class Action
    {
        Idle, Running, Attacking
    };
    void loopAnimation(Action action);

    Action m_action = Action::Idle;
    std::unordered_map<Action, Animation> m_animations;
    const sf::Texture* m_currentTexture = nullptr;
};
