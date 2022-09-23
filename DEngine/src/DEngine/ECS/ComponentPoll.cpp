#include "ComponentPoll.h"
#include <memory>
namespace DEngine {

    unsigned int ComponentPoll::Add()
    {
        m_Size += m_ComponentSize;
        realloc(m_Start, m_Size);
        return m_Size / m_ComponentSize;
    }

    void ComponentPoll::Remove(unsigned int index)
    {
        char* ca = m_Start + (m_ComponentSize * index); //Element address
        char* nca = ca + m_ComponentSize; //Next Element address
        size_t cpysize = m_Size - (nca - m_Start);
        memcpy(ca, nca, cpysize);
        
        m_Size -= cpysize ? m_ComponentSize : 0;
    }

    void* ComponentPoll::GetComponent(unsigned int index) const
    {
        return static_cast<void*>(m_Start + (m_ComponentSize * index));
    }
}