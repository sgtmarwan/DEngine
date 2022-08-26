#include "D3D11Shader.h"
namespace DEngine
{
	Direct3D11Context* D3D11Shader::graphicsContext = nullptr;

	void D3D11Shader::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}


	D3D11ShaderData::~D3D11ShaderData()
	{
		for (unsigned int i = 0; i < DataCount; ++i)
			Data[i]->Release();
		delete[DataCount] Data;
	}

	bool D3D11Shader::isVSBound()
	{
		ID3D11VertexShader* vs;
		graphicsContext->GetDeviceContext()->VSGetShader(&vs, nullptr, nullptr);
		if (vs == VertexShader)
			return true;
		return false;
	}
	bool D3D11Shader::isPSBound()
	{
		ID3D11PixelShader* ps;
		graphicsContext->GetDeviceContext()->PSGetShader(&ps, nullptr, nullptr);
		if (ps == PixelShader)
			return true;
		return false;
	}

	D3D11Shader::D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout) :
		VertexShader(vertexShader), PixelShader(pixelShader), InputLayout(inputLayout)
	{
	}
	void D3D11Shader::Bind()
	{
		graphicsContext->GetDeviceContext()->VSSetShader(VertexShader, NULL, NULL);
		graphicsContext->GetDeviceContext()->PSSetShader(PixelShader, NULL, NULL);
		graphicsContext->GetDeviceContext()->IASetInputLayout(InputLayout);
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