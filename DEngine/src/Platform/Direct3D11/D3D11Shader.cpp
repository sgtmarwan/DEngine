#include "D3D11Shader.h"
#include "Direct3D11Context.h"
namespace DEngine
{

	void D3D11Shader::Bind() const
	{
		Direct3D11Context::Get()->GetDeviceContext()->VSSetShader(VertexShader, nullptr, 0);
		Direct3D11Context::Get()->GetDeviceContext()->PSSetShader(PixelShader, nullptr, 0);
		Direct3D11Context::Get()->GetDeviceContext()->IASetInputLayout(InputLayout);
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