#include "Pool.h"
#include <algorithm>
#include <iostream>
namespace Entita
{

Entity::Ptr Pool::CreateEntity()
{
    auto entity = std::make_shared<Entity>();
    m_entities.push_back(entity);
    return entity;
}

void Pool::RemoveEntity(Entity::Ptr entity)
{
    auto iter = std::remove_if(m_entities.begin(), m_entities.end(), [&](auto& e)
    {
        return e == entity;
    });
    m_entities.erase(iter, m_entities.end());
}

void Pool::Process()
{
    for(auto& system : m_systems)
    {
        system->Process();
    }
}

}
