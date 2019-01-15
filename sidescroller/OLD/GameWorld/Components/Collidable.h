#pragma once

enum class CollisionSide
{
	None = 0,
    Left = 1UL << 1,
    Right = 1UL << 2,
    Top = 1UL << 3,
    Down = 1UL << 4,
};

struct Collidable
{
    void Reset();
    void Add(CollisionSide side);
    bool Has(CollisionSide side) const;

    bool IsGrounded() const;
private:
    unsigned m_collisionSides = 0;
};
