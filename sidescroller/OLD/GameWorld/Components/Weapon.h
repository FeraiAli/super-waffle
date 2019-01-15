#pragma once
#include <chrono>

struct Weapon
{
    using Duration = std::chrono::milliseconds;
    enum class Type
    {
        Gun
    };

    bool ReadyToAttack()
    {
        if(Type::Gun == type)
        {
            return delayToAttackCounter >= Duration(250);
        }
        return false;
    }

    const Type type = Type::Gun;
    Duration delayToAttackCounter = Duration(0);
	bool onAttackBegin = false;
};
