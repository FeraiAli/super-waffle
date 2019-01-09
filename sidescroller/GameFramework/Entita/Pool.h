#pragma once
#include "BaseSystem.h"
#include "Entity.h"
#include <set>
#include <vector>
#include <typeindex>

namespace Entita
{

class Pool : public std::enable_shared_from_this<Pool>
{
public:
    Entity::Ptr CreateEntity();
    void RemoveEntity(Entity::Ptr entity);

    void Process();

    template<typename System>
    std::shared_ptr<System> RegisterSystem();

    template<typename... Components>
    std::vector<Entity::Ptr> GetEntities();

    template<typename... Components>
    void ForEach(std::function<void(Entity::Ptr, Components&...)>&& fn);

    template<typename... Components>
    Entity::Ptr GetSingleEntity();
//private:
    std::vector<Entity::Ptr> m_entities;
    std::unordered_map<size_t, BaseSystem::Ptr> m_systems;
};


template<typename System>
std::shared_ptr<System> Pool::RegisterSystem()
{
    static_assert(std::is_base_of<BaseSystem, System>::value, "System must be derived from BaseSystem!");

    const auto systemHash = std::type_index(typeid(System)).hash_code();
    assert(m_systems.find(systemHash) == m_systems.end() and "System is already registered!");

    auto system = std::make_shared<System>();
    system->Init();
    m_systems[systemHash] = system;
    return system;
}

template<typename... Components>
void Pool::ForEach(std::function<void(Entity::Ptr, Components&...)>&& fn)
{
    for(auto& entity : m_entities)
    {
        if(entity->HasComponent<Components...>())
        {
            fn(entity, entity->GetComponent<Components>()...);
        }
    }
}

template<typename... Components>
std::vector<Entity::Ptr> Pool::GetEntities()
{
    std::vector<Entity::Ptr> entities;
    for(auto& entity : m_entities)
    {
        if(entity->HasComponent<Components...>())
        {
            entities.push_back(entity);
        }
    }
    return entities;
}

template<typename... Components>
Entity::Ptr Pool::GetSingleEntity()
{
    Entity::Ptr singleEntity;
    for(auto& entity : m_entities)
    {
        if(entity->HasComponent<Components...>())
        {
            assert(nullptr == singleEntity and "Trying to GetSingleEntity, but found more than one!");
            singleEntity = entity;
        }
    }
    assert(nullptr != singleEntity and "Trying to GetSingleEntity, that doesn't exist!");
    return singleEntity;
}

} // end of namespace Entita
