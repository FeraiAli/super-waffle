#pragma once
#include "Easing.h"
#include "../Common/ConstexprIf.hpp"
#include "../Common/TypeTraits.hpp"

namespace Core
{
namespace Tween
{

///Get value between range [start, end] - by progress factor (t) - between 0.0 and 1.0
template<typename T>
T Lerp(T start, T end, double t)
{
    return (start + (t * (end-start)));
}

template<typename T, typename R>
R RangeMap(T in, T inStart, T inEnd, R outStart, R outEnd, const Tween::Function& easing = Tween::linear)
{
    R result;

    constexpr bool isInChrono = Traits::is_chrono_duration<T>::value;
    constexpr bool isOutChrono = Traits::is_chrono_duration<R>::value;
    if_constexpr(isInChrono)
    {
        result = RangeMap(in.count(), inStart.count(), inEnd.count(), outStart, outEnd, easing);
    }
    else_if_constexpr(isOutChrono)
    {
        auto res64 = RangeMap(in, inStart, inEnd, outStart.count(), outEnd.count(), easing);
        result = static_cast<R>(res64);
    }
    else_if_constexpr(isInChrono && isOutChrono)
    {
        auto res64 = RangeMap(in.count(), inStart.count(), inEnd.count(),
                              outStart.count(), outEnd.count(), easing);
        result = static_cast<R>(res64);
    }
    else_constexpr
    {
        auto progress = in - inStart;
        auto inFactor = static_cast<double>(progress) / static_cast<double>(inEnd - inStart);
        inFactor = easing(inFactor);

        result = Lerp(outStart, outEnd, inFactor);
    }
    end_if_constexpr;

    return result;
}

} // end of Tween
} // end of Core
