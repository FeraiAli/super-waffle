#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cassert>

namespace Context
{

namespace Internal
{

struct InternalContext
{
    template<typename T, typename... Args>
    T& Add(Args&&... args)
    {
        const size_t hashCode = std::type_index(typeid(T)).hash_code();
        assert(m_components.find(hashCode) == m_components.end() and "Component is already added!");

        auto component = std::make_shared<T>(args...);
        m_components[hashCode] = component;
        return (*static_cast<T*>(component.get()));
    }

    template<typename T>
    T& Get()
    {
        const size_t hashCode = std::type_index(typeid(T)).hash_code();
        auto iter = m_components.find(hashCode);
        assert(iter != m_components.end() and "Component doesn't exist!");

        return (*static_cast<T*>(iter->second.get()));
    }

    template<typename T>
    bool Has()
    {
        const size_t hashCode = std::type_index(typeid(T)).hash_code();
        return m_components.find(hashCode) != m_components.end();
    }
private:
    std::unordered_map<size_t, std::shared_ptr<void>> m_components;
};

inline InternalContext& GetInternalContext()
{
    static InternalContext internalContext;
    return internalContext;
}

} //end of namespace Internal

template<typename T, typename... Args>
T& Add(Args&&... args)
{
    Internal::GetInternalContext().Add<T>(args...);
}

template<typename T>
T& Get()
{
    return Internal::GetInternalContext().Get<T>();
}

template<typename T>
bool Has()
{
    return Internal::GetInternalContext().Has<T>();
}

}



