#include <d3dcompiler.h>
#include "D3D11_INPUT_LAYOUT.h"
#include "D3D11_DATA_USAGE.h"
#include "D3D11GraphicsFactory.h"
#include "D3D11Shader.h"
#include "D3D11Sampler.h"
#include "D3D11Buffer.h"
#include "D3D11Texture2D.h"


namespace DEngine
{
	ID3D11VertexShader* D3D11GraphicsFactory::CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out) const
	{
		ID3D11VertexShader* vs;
		ID3DBlob* vs_blob;
		D3DCreateBlob(VSSize[0], &vs_blob);
		memcpy(vs_blob->GetBufferPointer(), VSSources[0], VSSize[0]);
		*vs_blob_out = vs_blob;
		auto hr = Direct3D11Context::Get()->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
		if (hr != S_OK)
			MessageBoxW(NULL, L"Error", NULL, NULL);
		return vs;
	}
	ID3D11PixelShader* D3D11GraphicsFactory::CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount) const
	{
		ID3D11PixelShader* ps;
		Direct3D11Context::Get()->GetDevice()->CreatePixelShader(PSSources[0], PSSize[0], nullptr, &ps);
		return ps;
	}
	ID3D11InputLayout* D3D11GraphicsFactory::CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob) const
	{
		ID3D11InputLayout* il;
		D3D11_INPUT_ELEMENT_DESC* inputElements = new D3D11_INPUT_ELEMENT_DESC[count];
		for (unsigned int i = 0; i < count; ++i)
			inputElements[i] = { inputLayout[i].Name, inputLayout[i].Slot, GetInputFormat(inputLayout[i].Format), 0, inputLayout[i].Offset, D3D11_INPUT_PER_VERTEX_DATA, 0};

		Direct3D11Context::Get()->GetDevice()->CreateInputLayout(inputElements, count, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &il);
		delete[] inputElements;
		return il;
	}
	Buffer* D3D11GraphicsFactory::CreateBuffer(const void* data, unsigned int size, DATA_USAGE usage, BUFFER_TYPE type) const
	{
		ID3D11Buffer* buff;
		D3D11_BUFFER_DESC bd = {};
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;
		bd.BindFlags = GetBufferType(type);
		bd.ByteWidth = size;
		bd.Usage = GetUsage(usage);
		bd.CPUAccessFlags = GetCPUAccessFlags(usage);

		sd.pSysMem = data;
		Direct3D11Context::Get()->GetDevice()->CreateBuffer(&bd, &sd, &buff);
		D3D11Buffer* buffer = new D3D11Buffer(buff);
		return buffer;
	}
	Shader* D3D11GraphicsFactory::CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount) const
	{
		ID3DBlob* vs_blob;
		ID3D11VertexShader* vs = CreateVertexShader(VSSources, VSSize, VSCount, &vs_blob);
		ID3D11PixelShader* ps = CreatePixelShader(PSSources, PSSize, PSCount);
		ID3D11InputLayout* il = CreateInputLayout(inputLayout, inputElementsCount, vs_blob);
		vs_blob->Release();
		Shader* shader = new D3D11Shader(vs, ps, il);
		return shader;
	}
	Texture2D* D3D11GraphicsFactory::CreateTexture2D(const void* image, unsigned int width, unsigned int height, TEXTURE2D_FORMAT format, DATA_USAGE usage, unsigned int mipLevels) const
	{
		ID3D11Texture2D* texture;
		ID3D11ShaderResourceView* srv;


		UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
		UINT miscFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;


		if (mipLevels == 1)
		{
			sd.pSysMem = image;
			sd.SysMemPitch = width * GetTexture2DPixelSize(format);
			sd.SysMemSlicePitch = 0;

		}
		else 
		{
			bindFlags |= D3D11_BIND_RENDER_TARGET;
			miscFlags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;

		}
		D3D11_TEXTURE2D_DESC td;
		td.Width = width;
		td.Height = height;
		td.MipLevels = mipLevels;
		td.BindFlags = bindFlags;
		td.SampleDesc = { 1,0 };
		td.CPUAccessFlags = GetCPUAccessFlags(usage);
		td.Usage = GetUsage(usage);
		td.Format = GetTexture2DFormat(format);
		td.MiscFlags = miscFlags;
		td.ArraySize = 1;

		if (mipLevels != 1)
		{
			Direct3D11Context::Get()->GetDevice()->CreateTexture2D(&td, nullptr, &texture);
			Direct3D11Context::Get()->GetDeviceContext()->UpdateSubresource(texture, 0, nullptr, image, width * GetTexture2DPixelSize(format), 0);//, D3D11_COPY_DISCARD);
		} 
		else Direct3D11Context::Get()->GetDevice()->CreateTexture2D(&td, &sd, &texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		srvd.Format = td.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = (mipLevels == 0) ? -1 : mipLevels;

		Direct3D11Context::Get()->GetDevice()->CreateShaderResourceView(texture, &srvd, &srv);
		if (mipLevels != 1)
			Direct3D11Context::Get()->GetDeviceContext()->GenerateMips(srv);
		Texture2D* tex = new D3D11Texture2D(texture, srv);
		return tex;
	}
	Sampler* D3D11GraphicsFactory::CreateSampler() const
	{
		ID3D11SamplerState* ss;
		D3D11_SAMPLER_DESC sd = {};
		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
		sd.MinLOD = 0;
		sd.MaxLOD = D3D11_FLOAT32_MAX;
		Direct3D11Context::Get()->GetDevice()->CreateSamplerState(&sd, &ss);
		D3D11Sampler* sampler = new D3D11Sampler(ss);
		return sampler;
	}
}
