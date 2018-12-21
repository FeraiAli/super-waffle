#include "ScaleBy.h"
#include <Libraries/Tweeny/Comparators.h>

namespace Core
{

ScaleBy::ScaleBy(sf::Sprite &sprite,
                 sf::Vector2f offset,
                 ScaleBy::Milli duration,
                 const Tween::Function &easeFunc)
    : m_spritePtr(&sprite)
{
    tweeny.AddTarget(sf::Vector2f())
          .AddTarget(offset)
          .During(duration)
          .Via(easeFunc);
    tweeny.Start();
}

Status ScaleBy::operator()()
{
    tweeny.Update(15ms);
    m_spritePtr->scale(tweeny.GetDelta());
    if(tweeny.IsRunning())
    {
        return Status::Running;
    }
    return Status::Finished;
}

} //end of Core
