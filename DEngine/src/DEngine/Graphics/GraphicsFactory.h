#pragma once
#include "INPUT_LAYOUT.h"
#include "Shader.h"
#include "DATA_USAGE.h"
#include "Buffer.h"
#include "Texture2D.h"
#include "Sampler.h"
namespace DEngine
{
	class GraphicsFactory
	{
	public:
		virtual ~GraphicsFactory() = default;
		virtual Buffer* CreateBuffer(const void* data, unsigned int size, DATA_USAGE usage, BUFFER_TYPE type) const = 0;
		virtual Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const = 0;
		virtual Texture2D* CreateTexture2D(const void* image, unsigned int width, unsigned int height, TEXTURE2D_FORMAT format, DATA_USAGE usage, unsigned int mipLevels) const = 0;
		virtual Sampler* CreateSampler() const = 0; //TODO: ADD More Options
	private:
		static GraphicsFactory* s_GraphicsFactory;
	public:
		static void Set(GraphicsFactory* gf);
		static GraphicsFactory* Get();
	};
}

