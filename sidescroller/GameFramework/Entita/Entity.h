#pragma once
#include "ComponentId.h"
#include <unordered_map>
#include <memory>
#include <cassert>

namespace Entita
{

class Entity
{
public:
    using Ptr = std::shared_ptr<Entity>;
    using Tag = size_t;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    T& GetComponent();

    template<typename T>
    void RemoveComponent();

    template<typename T>
    bool HasComponent();

    template<typename First, typename Second, typename... Remaining>
    bool HasComponent();

    std::weak_ptr<Entity> Owner;
private:
    using ComponentPtr = std::shared_ptr<void>;
    std::unordered_map<size_t, ComponentPtr> m_components;
    size_t m_combinedId = 0;
};

template<typename T, typename... Args>
T& Entity::AddComponent(Args&&... args)
{
    auto compId = GetComponentId<T>();
    assert(compId < 64 and "You reached maximum limit of components, time to refactor code and use bitset instead!");

    auto iter = m_components.find(compId);
    assert(iter == m_components.end() and "Component already exist in this Entity");

    auto comp = std::make_shared<T>(args...);
    m_components[compId] = comp;
    m_combinedId |= (1UL << compId);
    return *(static_cast<T*>(comp.get()));
}

template<typename T>
T& Entity::GetComponent()
{
    auto compId = GetComponentId<T>();
    auto iter = m_components.find(compId);
    assert(iter != m_components.end() and "Component doesn't exist in this Entity");

    return *(static_cast<T*>(iter->second.get()));
}

template<typename T>
void Entity::RemoveComponent()
{
    auto compId = GetComponentId<T>();
    m_components.erase(compId);
    m_combinedId &= ~(1UL << compId);
}

template<typename T>
bool Entity::HasComponent()
{
    auto compId = GetComponentId<T>();
    return ((m_combinedId >> compId) & 1UL);
}

template<typename First, typename Second, typename... Remaining>
bool Entity::HasComponent()
{
    return HasComponent<First>() and HasComponent<Second, Remaining...>();
}

} //end of namespace Entita
