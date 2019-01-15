#pragma once
#include <functional>
#include <chrono>

namespace Action
{
using Duration = std::chrono::milliseconds;
enum class Status
{
    Running, Finished
};
using ActionFn = std::function<Status()>;
} // end of namespace
