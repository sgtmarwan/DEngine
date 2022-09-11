#pragma once
#include "INPUT_LAYOUT.h"
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Texture2D.h"
namespace DEngine
{
	enum class DATA_USAGE
	{
		GRW = 0, GR, GR_CW, GW_CR
	};
	class GraphicsFactory
	{
	protected:

	public:
		virtual ~GraphicsFactory() = default;
		virtual ShaderData* CreateShaderData(void* data, unsigned int size, DATA_USAGE usage) const = 0;
		virtual VertexBuffer* CreateVertexBuffer(void* vertices, unsigned int stride, unsigned int verticesCount, DATA_USAGE usage) const = 0;
		virtual Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const = 0;
		virtual Mesh* CreateMesh(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, DATA_USAGE usage) const = 0;
		virtual Texture2D* CreateTexture2D(const void* image, unsigned int width, unsigned int height, TEXTURE2D_FOMAT format, DATA_USAGE usage, unsigned int mipLevels) const = 0;
		virtual Sampler* CreateSampler() const = 0; //TODO: ADD More Options
	};
}

