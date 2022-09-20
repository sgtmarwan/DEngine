#pragma once
#include "Math/Vector4.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
namespace DEngine
{
	enum class GraphicsAPI
	{
		Direct3D11 = 0
	};
	class GraphicsContext
	{
		friend class WinWindow;
	protected:
		unsigned short m_BackBufferCount;
		unsigned short m_Vsync;
		unsigned short m_CurrentBackBuffer = 0;
	protected:
		virtual void Resize(unsigned int width, unsigned int height) = 0;
	public:
		virtual ~GraphicsContext() = default;
		GraphicsContext(unsigned short backBufferCount, unsigned short vsync);
		virtual void PresentFrame() = 0;
		virtual void SetRes(unsigned int width, unsigned int height) = 0;
		virtual void Draw(unsigned int indicesCount) const = 0;
		virtual void ClearBackBuffer(const Vector4& color) = 0;
		virtual void ClearDepthBuffer(float depth) = 0;
	};
}

