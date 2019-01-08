#pragma once

enum class AgentTag
{
     Drawable       = 1 << 0
    ,Collision      = 1 << 1
    ,AI             = 1 << 2
    ,WASDControl    = 1 << 3
    ,ArrowsControl  = 1 << 4
    ,Gravity        = 1 << 5
};
