#pragma once
#include <functional>

namespace Core
{

enum class Status
{
    Running, Finished
};
using ActionFn = std::function<Status()>;

}
