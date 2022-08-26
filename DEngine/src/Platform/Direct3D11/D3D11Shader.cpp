#include "D3D11Shader.h"
namespace DEngine
{
	Direct3D11Context* D3D11Shader::graphicsContext = nullptr;

	D3D11ShaderData::~D3D11ShaderData()
	{
		for (int i = 0; i < DataCount; ++i)
			Data[i]->Release();
		delete[DataCount] Data;
		delete[DataCount] Size;
	}

	D3D11Shader::D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout) :
		VertexShader(vertexShader), PixelShader(pixelShader), InputLayout(inputLayout)
	{
	}
	void D3D11Shader::Bind()
	{
		graphicsContext->GetDeviceContext()->VSSetShader(VertexShader, NULL, NULL);
		graphicsContext->GetDeviceContext()->PSSetShader(PixelShader, NULL, NULL);
	}
	void D3D11Shader::SetVSShaderData(ShaderData* data, unsigned int startIndex)
	{
		D3D11ShaderData* Data = (D3D11ShaderData*)data;
		graphicsContext->GetDeviceContext()->VSSetConstantBuffers(startIndex, Data->DataCount, Data->Data);
	}
	void D3D11Shader::SetPSShaderData(ShaderData* data, unsigned int startIndex)
	{
		D3D11ShaderData* Data = (D3D11ShaderData*)data;
		graphicsContext->GetDeviceContext()->PSSetConstantBuffers(startIndex, Data->DataCount, Data->Data);
	}
	D3D11Shader::~D3D11Shader()
	{
		if (VertexShader != nullptr) VertexShader->Release();
		if (PixelShader != nullptr) PixelShader->Release();
		if (InputLayout != nullptr) InputLayout->Release();
	}
}