#include "D3D11Shader.h"
namespace DEngine
{
	Direct3D11Context* D3D11Shader::graphicsContext = nullptr;
	void D3D11Shader::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	D3D11ShaderData::D3D11ShaderData(ID3D11Buffer* data) : 
		Data(data)
	{

	}


	Direct3D11Context* D3D11ShaderData::graphicsContext = nullptr;
	void D3D11ShaderData::SetGraphicsContext(Direct3D11Context* gc)
	{
		graphicsContext = gc;
	}

	D3D11ShaderData::~D3D11ShaderData()
	{
		if (Data != nullptr) Data->Release();
	}
	void D3D11ShaderData::VSSet(const unsigned int slot) const
	{
		graphicsContext->GetDeviceContext()->VSSetConstantBuffers(slot, 1, &Data);
	}
	void D3D11ShaderData::PSSet(const unsigned int slot) const 
	{
		graphicsContext->GetDeviceContext()->PSSetConstantBuffers(slot, 1, &Data);
	}

	void D3D11Shader::Bind() const
	{
		graphicsContext->GetDeviceContext()->VSSetShader(VertexShader, nullptr, 0);
		graphicsContext->GetDeviceContext()->PSSetShader(PixelShader, nullptr, 0);
		graphicsContext->GetDeviceContext()->IASetInputLayout(InputLayout);
	}


	D3D11Shader::D3D11Shader(ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, ID3D11InputLayout* inputLayout) :
		VertexShader(vertexShader), PixelShader(pixelShader), InputLayout(inputLayout)
	{
	}
	D3D11Shader::~D3D11Shader()
	{
		if (VertexShader != nullptr) VertexShader->Release();
		if (PixelShader != nullptr) PixelShader->Release();
		if (InputLayout != nullptr) InputLayout->Release();
	}
}