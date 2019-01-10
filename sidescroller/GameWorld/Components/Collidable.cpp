#include "Collidable.h"

void Collidable::Reset()
{
    m_collisionSides = 0;
}

void Collidable::Add(CollisionSide side)
{
    m_collisionSides |= static_cast<unsigned>(side);
}

bool Collidable::Has(CollisionSide side) const
{
    return m_collisionSides & static_cast<unsigned>(side);
}

bool Collidable::IsGrounded() const
{
    return Has(CollisionSide::Down);
}

