#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/GraphicsFactory.h"
namespace DEngine
{
	class D3D11GraphicsFactory : public GraphicsFactory
	{
	private:
		ID3D11VertexShader* CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out) const;
		ID3D11PixelShader* CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount) const;
		ID3D11InputLayout* CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob) const;
	public:
		D3D11GraphicsFactory() = default;
		virtual ~D3D11GraphicsFactory() = default;
		Buffer* CreateBuffer(const void* data, unsigned int size, DATA_USAGE usage, BUFFER_TYPE type) const override;
		Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const override;
		Texture2D* CreateTexture2D(const void* image, unsigned int width, unsigned int height, TEXTURE2D_FORMAT format, DATA_USAGE usage, unsigned int mipLevels) const override;
		Sampler* CreateSampler() const override;
	};
}

