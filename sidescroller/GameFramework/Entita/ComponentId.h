#pragma once
#include <cstdlib>

namespace Entita
{
namespace Internal
{
struct UniqueComponentId
{
    static size_t Get()
    {
        static size_t FreeId = 1;
        return FreeId++;
    }
};
}

template<typename T>
size_t GetComponentId()
{
    static const size_t CompId = Internal::UniqueComponentId::Get();
    return CompId;
}

}
