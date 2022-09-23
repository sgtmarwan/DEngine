#include "EntityManager.h"

namespace DEngine
{
	unsigned int EntityManager::s_ComponentId = 0;

	unsigned long long EntityManager::Create()
	{
		static unsigned long long s_ID = 0ll;
		unsigned long long id;
		if (m_AID.empty())
		{
			id = ++s_ID;
			m_Entities[id] = Entity();
			return id;
		}
		else
		{
			id = m_AID.front();
			m_AID.pop();
			m_Entities[id] = Entity();
			return id;
		}
	}
	void EntityManager::Destroy(unsigned long long entity)
	{
		m_Entities.erase(entity);
		m_AID.push(entity);
	}
	void EntityManager::Entity::AddComponent(unsigned int type, unsigned index)
	{
		m_Components[type] = index;
	}
	unsigned int EntityManager::Entity::GetComponentIndex(unsigned int type)
	{
		if (m_Components.contains(type))
			return m_Components[type];
		return NOCOMPONENT;
	}
	void EntityManager::Entity::RemoveComponent(unsigned int type)
	{
		if (m_Components.contains(type))
			m_Components.erase(type);
	}
}