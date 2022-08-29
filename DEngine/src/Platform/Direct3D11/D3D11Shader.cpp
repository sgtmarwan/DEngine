#include "D3D11Shader.h"
namespace DEngine
{

	D3D11ShaderData::~D3D11ShaderData()
	{
		for (unsigned int i = 0; i < DataCount; ++i)
			Data[i]->Release();
		delete[DataCount] Data;
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