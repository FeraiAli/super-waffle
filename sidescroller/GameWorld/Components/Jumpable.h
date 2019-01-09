#pragma once
#include <chrono>

struct Jumpable
{
    using Duration = std::chrono::milliseconds;

    bool isJumping = false;

    Duration jumpTimeCounter = Duration::zero();
    Duration afterFallJumpCounter = Duration::zero();
};
