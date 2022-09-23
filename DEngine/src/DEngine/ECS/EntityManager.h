#pragma once
#include "ComponentPoll.h"
#include "ComponentGroup.h"
#include <unordered_map>
#include <queue>
namespace DEngine
{
	
	class EntityManager
	{
	private:
		class Entity
		{
		public:
#define NOCOMPONENT 0xffffffff;

			Entity() = default;
			~Entity() = default;
		public:
			void AddComponent(unsigned int type, unsigned index);
			unsigned int GetComponentIndex(unsigned int type);
			void RemoveComponent(unsigned int type);
		private:
			std::unordered_map<unsigned int, unsigned int> m_Components;
		};
	public:
		EntityManager() = default;
		~EntityManager() = default;
	public:
		unsigned long long Create();
		void Destroy(unsigned long long entity);

		template<typename T>
		void AddComponent(unsigned long long entity)
		{
			unsigned int id = GetComponentId<T>();
			if(m_Entities.contains(entity))
			{
				m_Entities[entity].AddComponent(GetComponentId<T>(), m_Components[GetComponentId<T>()].Add());
			}
		}
		template<typename T>
		void RemoveComponent(unsigned long long entity)
		{
			unsigned int id = GetComponentId<T>();
			if (m_Entities.contains(entity))
			{
				m_Entities[entity].RemoveComponent(id);
				if (m_Components[id].Empty())
					m_Components.erase(id);
			}
		}
		template<typename T>
		T* GetComponent(unsigned long long entity)
		{
			unsigned int id = GetComponentId<T>();
			if (m_Entities.contains(entity))
				return static_cast<T*>(m_Components[id].GetComponent(m_Entities[entity].GetComponentIndex(id)));
		}
		template<typename T>
		ComponentGroup<T> GetComponentGroup()
		{
			return ComponentGroup<T>(m_Components[GetComponentId<T>()]);
		}
	private:
		static unsigned int s_ComponentId;
		template<typename T>
		unsigned int GetComponentId()
		{
			static unsigned int ComponentId = ++s_ComponentId;
			if (!m_Components.contains(ComponentId))
				m_Components[ComponentId] = ComponentPoll(sizeof(T));
			return ComponentId;
		}
		std::unordered_map<unsigned long long, Entity> m_Entities;
		std::unordered_map<unsigned int, ComponentPoll> m_Components;

		std::queue<unsigned long long> m_AID;
	};
}

