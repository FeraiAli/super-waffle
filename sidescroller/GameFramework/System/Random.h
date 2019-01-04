#pragma once
#include "TraitsHelper.hpp"
#include <random>

class Random
{
public:
    Random();
    Random(int64_t seed);

    bool operator()(double probability);

    template<typename T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T, typename std::enable_if_t<std::is_enum<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T, typename std::enable_if_t<is_chrono_duration<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T, typename std::enable_if_t<is_SFML_Vector2<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T, typename std::enable_if_t<is_iterator<T>::value>* = nullptr>
    T operator()(T min, T max);

    template<typename T>
    T operator()(const std::initializer_list<T>& list);
private:
    std::default_random_engine m_engine;
};

template<typename T, typename std::enable_if_t<std::is_integral<T>::value>*>
T Random::operator()(T min, T max)
{
    return std::uniform_int_distribution<T>(min, max)(m_engine);
}

template<typename T, typename std::enable_if_t<std::is_enum<T>::value>*>
T Random::operator()(T min, T max)
{
    auto min64 = static_cast<int64_t>(min);
    auto max64 = static_cast<int64_t>(max);
    auto res64 = std::uniform_int_distribution<int64_t>(min64, max64)(m_engine);
    return static_cast<T>(res64);
}

template<typename T, typename std::enable_if_t<std::is_floating_point<T>::value>*>
T Random::operator()(T min, T max)
{
    return std::uniform_real_distribution<T>(min, max)(m_engine);
}

template<typename T, typename std::enable_if_t<is_chrono_duration<T>::value>*>
T Random::operator()(T min, T max)
{
    auto res64 = std::uniform_int_distribution<int64_t>(min.count(), max.count())(m_engine);
    return static_cast<T>(res64);
}

template<typename T, typename std::enable_if_t<is_SFML_Vector2<T>::value>*>
T Random::operator()(T min, T max)
{
    T result;
    result.x = operator()(min.x, max.x);
    result.y = operator()(min.y, max.y);
    return result;
}

template<typename T, typename std::enable_if_t<is_iterator<T>::value>*>
T Random::operator()(T min, T max)
{
    const auto size = std::distance(min, max);
    if( size <= 0 )
    {
        return max;
    }
    else
    {
        using diff_t = typename std::iterator_traits<T>::difference_type;
        auto randomIdx = std::uniform_int_distribution<int64_t>(0, size - 1)(m_engine);
        return std::next(min, static_cast<diff_t>(randomIdx));
    }
}

template<typename T>
T Random::operator()(const std::initializer_list<T>& list)
{
    return *operator()(list.begin(), list.end());
}

