#pragma once
#include <random>
#include <chrono>
#include "Libraries/Common/ConstexprIf.hpp"
#include "Libraries/Common/TypeTraits.hpp"

namespace Core
{

class Random
{
public:
    Random(int64_t seed);
    Random();

    bool operator()(double probability);

    template<typename T>
    T operator()(T min, T max)
    {
        T result;
        if_constexpr(std::is_integral<T>::value)
        {
            result = std::uniform_int_distribution<T>(min, max)(m_engine);
        }
        else_if_constexpr(std::is_enum<T>::value)
        {
            auto min64 = static_cast<int64_t>(min);
            auto max64 = static_cast<int64_t>(max);
            auto res64 = std::uniform_int_distribution<int64_t>(min64, max64)(m_engine);
            result = static_cast<T>(res64);
        }
        else_if_constexpr(std::is_floating_point<T>::value)
        {
            result = std::uniform_real_distribution<T>(min, max)(m_engine);
        }
        else_if_constexpr(Traits::is_chrono_duration<T>::value)
        {
            auto res64 = std::uniform_int_distribution<int64_t>(min.count(), max.count())(m_engine);
            result = static_cast<T>(res64);
        }
        else_if_constexpr(Traits::is_iterator<T>::value)
        {
            const auto size = std::distance(min, max);
            if( size <= 0 )
            {
                result = max;
            }
            else
            {
                using diff_t = typename std::iterator_traits<T>::difference_type;
                auto randomIdx = std::uniform_int_distribution<int64_t>(0, size - 1)(m_engine);
                result = std::next(min, static_cast<diff_t>(randomIdx));
            }
        }
        else_constexpr
        {
            static_assert(true, "Trying to get random value between not supported types!");
        }
        end_if_constexpr;

        return result;
    }
private:
    std::default_random_engine m_engine;
};

} //end of core
