#include "Shader.h"

namespace DEngine
{
    Shader::Shader()
    {
        static unsigned int id = 0;
        m_Id = ++id;
    }

    unsigned int Shader::GetId() const
    {
        return m_Id;
    }
}