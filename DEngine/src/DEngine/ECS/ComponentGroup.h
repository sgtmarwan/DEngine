#pragma once
#include "ComponentPoll.h"
namespace DEngine {
	template<typename T>
	class ComponentGroup
	{
		friend class EntityManager;
	private:
		ComponentGroup(const ComponentPoll& cp) :
			m_ComponentPoll(cp);
		{

		}
		const ComponentPoll& m_ComponentPoll;
	public:
		ComponentGroup() = delete;
		const T& GetComponent(unsigned int index)
		{
			return *static_cast<T*>m_ComponentPoll.GetComponent(index);
		}
		size_t size()
		{
			return m_ComponentPoll.GetSize();
		}
	};
}