#pragma once
#include "Easing.h"
#include "../Common/TraitsHelper.hpp"

namespace Math
{

template<typename T>
T Lerp(T start, T end, double t)
{
    return (start + (t * (end-start)));
}

template<typename T, typename R>
R RangeMap(T in, T inStart, T inEnd, R outStart, R outEnd, const Easing::Function& easing = Easing::linear)
{
    auto progress = in - inStart;
    auto inFactor = static_cast<double>(progress) / static_cast<double>(inEnd - inStart);
    inFactor = easing(inFactor);

    R result = Lerp(outStart, outEnd, inFactor);
    return result;
}

//template<typename T, typename R, typename std::enable_if_t<is_chrono_duration<T>::value>* = nullptr>
//R RangeMap(T in, T inStart, T inEnd, R outStart, R outEnd, const Easing::Function& easing = Easing::linear)
//{
//    return RangeMap(in.count(), inStart.count(), inEnd.count(), outStart, outEnd, easing);
//}

//template<typename T, typename R, typename std::enable_if_t<is_chrono_duration<R>::value>* = nullptr>
//R RangeMap(T in, T inStart, T inEnd, R outStart, R outEnd, const Easing::Function& easing = Easing::linear)
//{
//    auto res64 = RangeMap(in, inStart, inEnd, outStart.count(), outEnd.count(), easing);
//    return static_cast<R>(res64);
//}

//template<typename T, typename R,
//         typename std::enable_if_t<is_chrono_duration<T>::value and is_chrono_duration<R>::value>* = nullptr>
//R RangeMap(T in, T inStart, T inEnd, R outStart, R outEnd, const Easing::Function& easing = Easing::linear)
//{
//    auto res64 = RangeMap(in.count(), inStart.count(), inEnd.count(), outStart.count(), outEnd.count(), easing);
//    return static_cast<R>(res64);
//}

} //end of namespcace Math
