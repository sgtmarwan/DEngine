#pragma once
#include "Math/Vector4.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
namespace DEngine
{
	class GraphicsContext
	{
	protected:
		unsigned short BackBufferCount;
		unsigned short Vsync;
		unsigned short CurrentBackBuffer = 0;
	public:
		virtual ~GraphicsContext() = default;
		GraphicsContext(unsigned short backBufferCount, unsigned short vsync);
		virtual void PresentFrame() = 0;
		virtual void ChangeRes(unsigned int width, unsigned int height) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void Draw(unsigned int indicesCount) const = 0;
		virtual void ClearBackBuffer(Vector4 color, float depth, char stencil) = 0;
		virtual void BindShader(const Shader* shader) const = 0;
		virtual void BindMesh(const Mesh* mesh) const = 0;
		virtual void SetVSShaderData(const ShaderData* data, const unsigned int index) const = 0;
		virtual void SetPSShaderData(const ShaderData* data, const unsigned int index) const = 0;
		virtual void SetPSSampler(const Sampler* sampler, const unsigned int index) const = 0;
		virtual void SetPSTexture2D(const Texture2D* texture, const unsigned int index) const = 0;
	};
}

