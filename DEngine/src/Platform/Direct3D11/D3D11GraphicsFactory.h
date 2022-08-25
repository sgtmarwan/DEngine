#pragma once
#include "Direct3D11Context.h"
#include "DEngine/Graphics/GraphicsFactory.h"
namespace DEngine
{
	class D3D11GraphicsFactory : public GraphicsFactory
	{
	private:
		Direct3D11Context* graphicsContext;

	private:
		ID3D11VertexShader* CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out);
		ID3D11PixelShader* CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount);
		ID3D11InputLayout* CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob);
	public:
		D3D11GraphicsFactory(Direct3D11Context* _graphicsContext);
		virtual ~D3D11GraphicsFactory();
		virtual Shader CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount);
	};
}

