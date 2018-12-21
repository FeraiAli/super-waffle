#pragma once
#include <type_traits>
#include <chrono>

namespace Core
{
namespace Traits
{
    template<class T>
    struct is_chrono_duration : std::false_type {};

    template<class Rep, class Period>
    struct is_chrono_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

    template <typename T>
    struct is_iterator
    {
        static char test(...);
        template <typename U,
                  typename = typename std::iterator_traits<U>::difference_type,
                  typename = typename std::iterator_traits<U>::pointer,
                  typename = typename std::iterator_traits<U>::reference,
                  typename = typename std::iterator_traits<U>::value_type,
                  typename = typename std::iterator_traits<U>::iterator_category>
        static long test(U&&);

        constexpr static bool value = std::is_same<decltype(test(std::declval<T>())), long>::value;
    };
} //end of Traits
} //end of Core
