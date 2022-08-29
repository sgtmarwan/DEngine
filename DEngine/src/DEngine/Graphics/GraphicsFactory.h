#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
namespace DEngine
{
	enum class DATA_USAGE
	{
		GRW = 0, GR, GR_CW
	};
	class GraphicsFactory
	{
	protected:

	public:
		virtual ~GraphicsFactory() = default;
		virtual ShaderData* CreateShaderData(void** data, unsigned int* size, unsigned int count, DATA_USAGE usage) const = 0;
		virtual Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const = 0;
		virtual Mesh* CreateMesh(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount) const = 0;
		virtual Texture2D* CreateTexture2D(void* image, unsigned int width, unsigned int height, int format, unsigned int channelsNum, DATA_USAGE usage) const = 0;
		virtual Sampler* CreateSampler() const = 0; //TODO: ADD More Options
	};
}

