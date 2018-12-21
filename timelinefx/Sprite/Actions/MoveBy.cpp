#include "MoveBy.h"
#include <Libraries/Tweeny/Comparators.h>
namespace Core
{

///=============================================== MOVE BY ============================================== ///
MoveBy::MoveBy(sf::Sprite &sprite,
               sf::Vector2f offset,
               MoveBy::Milli duration,
               const Tween::Function& easeFunc)
    : m_spritePtr(&sprite)
{
    tweeny.AddTarget(sf::Vector2f())
          .AddTarget(offset)
          .During(duration)
          .Via(easeFunc);
    tweeny.Start();
}

Status MoveBy::operator()()
{
    tweeny.Update(15ms);
    m_spritePtr->move(tweeny.GetDelta());
    if(tweeny.IsRunning())
    {
        return Status::Running;
    }
    return Status::Finished;
}

} //end of Core
