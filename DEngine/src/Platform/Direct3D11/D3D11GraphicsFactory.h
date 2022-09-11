#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/INPUT_LAYOUT.h"
#include "DEngine/Graphics/GraphicsFactory.h"
namespace DEngine
{
	class D3D11GraphicsFactory : public GraphicsFactory
	{
	private:
		Direct3D11Context* graphicsContext;

	private:
		ID3D11VertexShader* CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out) const;
		ID3D11PixelShader* CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount) const;
		ID3D11InputLayout* CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob) const;
	public:
		D3D11GraphicsFactory(Direct3D11Context* _graphicsContext);
		~D3D11GraphicsFactory();
		ShaderData* CreateShaderData(void* data, unsigned int size, DATA_USAGE usage) const override;
		VertexBuffer* CreateVertexBuffer(void* vertices, unsigned int stride, unsigned int verticesCount, DATA_USAGE usage) const override;
		Mesh* CreateMesh(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount, DATA_USAGE usage) const override;
		Shader* CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const override;
		Texture2D* CreateTexture2D(const void* image, unsigned int width, unsigned int height, TEXTURE2D_FOMAT format, DATA_USAGE usage, unsigned int mipLevels) const override;
		Sampler* CreateSampler() const override;
	};
}

