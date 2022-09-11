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

	void D3D11ShaderData::UpdateData(void* data, unsigned int size, unsigned int offset)
	{
		D3D11_BOX box;
		ZeroMemory(&box, sizeof(D3D11_BOX));
		box.bottom = 1;
		box.back = 1;
		box.front = 0;
		box.top = 0;
		box.left = offset;
		box.right = offset + size;
		graphicsContext->GetDeviceContext()->UpdateSubresource1(Data, 0, &box, data, size, 0, D3D11_COPY_DISCARD);
	}

	void* D3D11ShaderData::GetDataPointer(bool wait) const
	{
		D3D11_MAPPED_SUBRESOURCE dms;
		graphicsContext->GetDeviceContext()->Map(Data, 0, D3D11_MAP_WRITE_DISCARD, wait ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT, &dms);
		return dms.pData;
	}

	void D3D11ShaderData::ReleaseDataPointer() const
	{
		graphicsContext->GetDeviceContext()->Unmap(Data, 0);
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