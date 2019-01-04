#pragma once
#include "SpriteTween.hpp"
#include "SpriteActionMacro.h"
#include <SFML/Graphics/Sprite.hpp>

namespace Action
{
#define SPRITE_ACTION_LIST(SPRITE_ACTION)                                    \
    SPRITE_ACTION(MoveTo, sf::Vector2f, setPosition, getPosition, true)      \
    SPRITE_ACTION(MoveBy, sf::Vector2f, setPosition, getPosition, false)     \
    SPRITE_ACTION(RotateTo, float, setRotation, getRotation, true)           \
    SPRITE_ACTION(RotateBy, float, setRotation, getRotation, false)          \
    SPRITE_ACTION(ScaleTo, sf::Vector2f, setScale, getScale, true)           \
    SPRITE_ACTION(ScaleBy, sf::Vector2f, setScale, getScale, false)          \

SPRITE_ACTION_LIST(SPRITE_ACTION_DECLARATION)
} //end of namespace
