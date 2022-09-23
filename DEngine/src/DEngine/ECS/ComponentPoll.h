#pragma once
namespace DEngine
{

	class ComponentPoll
	{
		friend class EntityManager;
	private:
		ComponentPoll(unsigned int size) :
			m_ComponentSize(size)
		{

		}
	public:
		ComponentPoll() = delete;
		unsigned int Add();
		void Remove(unsigned int index);
		void* GetComponent(unsigned int index) const;
		size_t GetSize() const { return m_Size / m_ComponentSize; }
		bool Empty() const { return m_Size == 0; }
	private:
		size_t m_Size;
		char* m_Start;
		unsigned int m_ComponentSize;
	};
}

