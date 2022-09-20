#pragma once
#include "Texture2D.h"
#include "Buffer.h"
#include "Sampler.h"
namespace DEngine
{
	class Shader
	{
	protected:
		unsigned int m_Id;
	public:
		Shader();
		virtual void Bind() const = 0;
		virtual ~Shader() = default;

		unsigned int GetId() const;
	};
}


