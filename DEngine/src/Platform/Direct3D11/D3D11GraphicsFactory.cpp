#include <d3dcompiler.h>

#include "D3D11GraphicsFactory.h"
#include "D3D11Shader.h"
#include "D3D11Mesh.h"
#include "D3D11Texture2D.h"




DXGI_FORMAT GetInputFormat(DEngine::INPUT_FORMAT format);				//Group into struct ???
DXGI_FORMAT GetTexture2DFormat(DEngine::TEXTURE2D_FOMAT format);
UINT GetTexture2DPixelSize(DEngine::TEXTURE2D_FOMAT format);
D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage);
int GetCPUAccessFlags(DEngine::DATA_USAGE usage);

namespace DEngine
{
	D3D11GraphicsFactory::D3D11GraphicsFactory(Direct3D11Context* _graphicsContext) : 
		graphicsContext(_graphicsContext)
	{

	}

	//TODO: ADD MULTPLE SHADER SOURCES SUPPORT

	ID3D11VertexShader* D3D11GraphicsFactory::CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out) const
	{
		ID3D11VertexShader* vs;
		ID3DBlob* vs_blob;
		D3DCreateBlob(VSSize[0], &vs_blob);
		memcpy(vs_blob->GetBufferPointer(), VSSources[0], VSSize[0]);
		*vs_blob_out = vs_blob;
		auto hr = graphicsContext->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
		if (hr != S_OK)
			MessageBoxW(NULL, L"Error", NULL, NULL);
		return vs;
	}
	ID3D11PixelShader* D3D11GraphicsFactory::CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount) const
	{
		ID3D11PixelShader* ps;
		graphicsContext->GetDevice()->CreatePixelShader(PSSources[0], PSSize[0], nullptr, &ps);
		return ps;
	}
	ID3D11InputLayout* D3D11GraphicsFactory::CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob) const
	{
		ID3D11InputLayout* il;
		D3D11_INPUT_ELEMENT_DESC* inputElements = new D3D11_INPUT_ELEMENT_DESC[count];
		for (unsigned int i = 0; i < count; ++i)
			inputElements[i] = { inputLayout[i].Name, inputLayout[i].Slot, GetInputFormat(inputLayout[i].Format), 0, inputLayout[i].Offset, D3D11_INPUT_PER_VERTEX_DATA, 0};
		graphicsContext->GetDevice()->CreateInputLayout(inputElements, count, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &il);
		delete[] inputElements;
		return il;
	}
	ShaderData* D3D11GraphicsFactory::CreateShaderData(void* data, unsigned int size, DATA_USAGE usage) const
	{
		ID3D11Buffer* buff;
		D3D11_BUFFER_DESC bd = {};
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.ByteWidth = size;
		bd.Usage = GetUsage(usage);
		bd.CPUAccessFlags = GetCPUAccessFlags(usage);

		sd.pSysMem = data;
		graphicsContext->GetDevice()->CreateBuffer(&bd, &sd, &buff);
		D3D11ShaderData* shaderData = new D3D11ShaderData(buff);
		return shaderData;
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
	Mesh* D3D11GraphicsFactory::CreateMesh(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount) const
	{
		ID3D11Buffer* vb;
		ID3D11Buffer* ib;
		D3D11_BUFFER_DESC bufferDesc = { };
		D3D11_SUBRESOURCE_DATA sr_data = { };
		bufferDesc.ByteWidth = sizeof(Vertex) * verticesCount;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		sr_data.SysMemPitch = 0;
		sr_data.SysMemSlicePitch = 0;
		sr_data.pSysMem = vertices;
		graphicsContext->GetDevice()->CreateBuffer(
			&bufferDesc,
			&sr_data,
			&vb);
		bufferDesc.ByteWidth = sizeof(unsigned int) * indicesCount;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		sr_data.pSysMem = indices;
		graphicsContext->GetDevice()->CreateBuffer(
			&bufferDesc,
			&sr_data,
			&ib);
		Mesh* msh = new D3D11Mesh(vb, ib, indicesCount);
		return msh;
	}
	Texture2D* D3D11GraphicsFactory::CreateTexture2D(void* image, unsigned int width, unsigned int height, TEXTURE2D_FOMAT format, DATA_USAGE usage, unsigned int mipLevels) const
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
			graphicsContext->GetDevice()->CreateTexture2D(&td, nullptr, &texture);
			graphicsContext->GetDeviceContext()->UpdateSubresource(texture, 0, nullptr, image, width * GetTexture2DPixelSize(format), 0);//, D3D11_COPY_DISCARD);
		} 
		else graphicsContext->GetDevice()->CreateTexture2D(&td, &sd, &texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		srvd.Format = td.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = (mipLevels == 0) ? -1 : mipLevels;

		graphicsContext->GetDevice()->CreateShaderResourceView(texture, &srvd, &srv);
		if (mipLevels != 1)
			graphicsContext->GetDeviceContext()->GenerateMips(srv);
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
		graphicsContext->GetDevice()->CreateSamplerState(&sd, &ss);
		D3D11Sampler* sampler = new D3D11Sampler(ss);
		return sampler;
	}
	D3D11GraphicsFactory::~D3D11GraphicsFactory()
	{

	}
}


DXGI_FORMAT GetInputFormat(DEngine::INPUT_FORMAT format)
{
	switch (format)
	{
	case DEngine::INPUT_FORMAT::int32_1:
		return DXGI_FORMAT_R32_SINT;
		break;
	case DEngine::INPUT_FORMAT::uint32_1:
		return DXGI_FORMAT_R32_UINT;
		break;
	case DEngine::INPUT_FORMAT::uint8_4:
		return DXGI_FORMAT_R8G8B8A8_UINT;
		break;
	case DEngine::INPUT_FORMAT::float32_1:
		return DXGI_FORMAT_R32_FLOAT;
		break;
	case DEngine::INPUT_FORMAT::float32_2:
		return DXGI_FORMAT_R32G32_FLOAT;
		break;
	case DEngine::INPUT_FORMAT::float32_3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
		break;
	case DEngine::INPUT_FORMAT::float32_4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	default:
		return DXGI_FORMAT_UNKNOWN;
		break;
	}
}

D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage)
{
	switch (usage)
	{
	case DEngine::DATA_USAGE::GRW:
		return D3D11_USAGE_DEFAULT;
		break;
	case DEngine::DATA_USAGE::GR:
		return D3D11_USAGE_IMMUTABLE;
		break;
	case DEngine::DATA_USAGE::GR_CW:
		return D3D11_USAGE_DYNAMIC;
		break;
	default:
		return D3D11_USAGE_DEFAULT;
		break;
	}
}
int GetCPUAccessFlags(DEngine::DATA_USAGE usage)
{
	switch (usage)
	{
	case DEngine::DATA_USAGE::GRW:
		return 0;
		break;
	case DEngine::DATA_USAGE::GR:
		return 0;
		break;
	case DEngine::DATA_USAGE::GR_CW:
		return D3D11_CPU_ACCESS_WRITE;
		break;
	default:
		return 0;
		break;
	}
}

DXGI_FORMAT GetTexture2DFormat(DEngine::TEXTURE2D_FOMAT format)
{
	switch (format)
	{
	case DEngine::TEXTURE2D_FOMAT::RGBA8_UNORM:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	default:
		return DXGI_FORMAT_UNKNOWN;
		break;
	}
}


UINT GetTexture2DPixelSize(DEngine::TEXTURE2D_FOMAT format)
{
	switch (format)
	{
	case DEngine::TEXTURE2D_FOMAT::RGBA8_UNORM:
		return 4;
		break;
	default:
		return 0;
		break;
	}
}