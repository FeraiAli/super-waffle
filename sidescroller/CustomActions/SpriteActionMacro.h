#pragma once

/////////////////////////////////// DECLARATION ///////////////////////////////////////

#define SPRITE_ACTION_DECLARATION(ActionName, Type,                         \
                                  Setter, Getter, IsTarget, ...)            \
                                                                            \
    struct ActionName : public SpriteAction::SpriteTween<Type>              \
    {                                                                       \
        explicit ActionName(std::shared_ptr<sf::Sprite> sprite,             \
                    Type target,                                            \
                    Duration duration,                                      \
                    const Tween::Function& function = Tween::linear);       \
        void OnBegin() final override;                                      \
        void OnStep(Type result) final override;                            \
    };                                                                      \


//////////////////////////////// IMPLEMENTATION /////////////////////////////////////

#define SPRITE_ACTION_IMPLEMENTATION(ActionName, Type,                              \
    Setter, Getter, IsTarget, ...)                                                  \
                                                                                    \
    ActionName::ActionName(std::shared_ptr<sf::Sprite> sprite,                      \
                   Type target,                                                     \
                   Duration duration,                                               \
                   const Tween::Function& function)                                 \
        : SpriteAction::SpriteTween<Type>(sprite, target, duration, function){}     \
                                                                                    \
    void ActionName::OnBegin()                                                      \
    {                                                                               \
        m_begin = m_sprite.lock()->Getter();                                        \
        if(false == IsTarget)                                                       \
            m_end += m_sprite.lock()->Getter();                                     \
    }                                                                               \
                                                                                    \
    void ActionName::OnStep(Type result)                                            \
    {                                                                               \
        m_sprite.lock()->Setter(result);                                            \
    }                                                                               \
