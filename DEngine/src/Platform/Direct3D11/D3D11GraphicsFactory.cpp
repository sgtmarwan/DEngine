#include <d3dcompiler.h>

#include "D3D11GraphicsFactory.h"
#include "D3D11Shader.h"
#include "D3D11Mesh.h"

#include <iostream>
#include <fstream>

DXGI_FORMAT GetInputFormat(DEngine::INPUT_FORMAT format);
D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage);
int GetCPUAccessFlags(DEngine::DATA_USAGE usage);

namespace DEngine
{
	D3D11GraphicsFactory::D3D11GraphicsFactory(Direct3D11Context* _graphicsContext) : 
		graphicsContext(_graphicsContext)
	{

	}

	//TODO: ADD MULTPLE SHADER SOURCES SUPPORT

	ID3D11VertexShader* D3D11GraphicsFactory::CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out)
	{
		HRESULT hr;
		ID3D11VertexShader* vs;
		ID3DBlob* vs_blob;
		D3DCreateBlob(VSSize[0], &vs_blob);
		*vs_blob_out = vs_blob;
		memcpy(vs_blob->GetBufferPointer(), VSSources[0], VSSize[0]);
		graphicsContext->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
		return vs;
	}
	ShaderData* D3D11GraphicsFactory::CreateShaderData(void** data, unsigned int* size, unsigned int count, DATA_USAGE usage)
	{
		ID3D11Buffer** buff = new ID3D11Buffer*[count];
		D3D11ShaderData* shaderData = new D3D11ShaderData();
		shaderData->DataCount = count;
		D3D11_BUFFER_DESC bd = {};
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;
		for (unsigned int i = 0; i < count; ++i)
		{
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.ByteWidth = size[i];
			bd.Usage = GetUsage(usage);
			bd.MiscFlags = 0;
			bd.StructureByteStride = 0;
			bd.CPUAccessFlags = GetCPUAccessFlags(usage);

			sd.pSysMem = data[i];
			graphicsContext->GetDevice()->CreateBuffer(&bd, &sd, &buff[i]);
		}
		shaderData->Data = buff;
		return shaderData;
	}
	ID3D11PixelShader* D3D11GraphicsFactory::CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount)
	{
		ID3D11PixelShader* ps;
		ID3DBlob* ps_blob;
		D3DCreateBlob(PSSize[0], &ps_blob);
		memcpy(ps_blob->GetBufferPointer(), PSSources[0], PSSize[0]);
		graphicsContext->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &ps);
		ps_blob->Release();
		return ps;
	}
	ID3D11InputLayout* D3D11GraphicsFactory::CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob)
	{
		ID3D11InputLayout* il;
		D3D11_INPUT_ELEMENT_DESC* inputElements = new D3D11_INPUT_ELEMENT_DESC[count];
		for (unsigned int i = 0; i < count; ++i)
			inputElements[i] = { inputLayout[i].Name, inputLayout[i].Index, GetInputFormat(inputLayout[i].Format), 0, inputLayout[i].Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		graphicsContext->GetDevice()->CreateInputLayout(inputElements, count, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &il);
		delete[count] inputElements;
		return il;
	}
	Shader* D3D11GraphicsFactory::CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount)
	{
		ID3DBlob* vs_blob;
		std::cout << "0\n";
		ID3D11VertexShader* vs = CreateVertexShader(VSSources, VSSize, VSCount, &vs_blob);
		std::cout << "1\n";
		ID3D11PixelShader* ps = CreatePixelShader(PSSources, PSSize, PSCount);
		std::cout << "2\n";
		ID3D11InputLayout* il = CreateInputLayout(inputLayout, inputElementsCount, vs_blob);
		std::cout << "3\n";
		vs_blob->Release();
		std::cout << "4\n";
		Shader* shader = new D3D11Shader(vs, ps, il);
		std::cout << "5\n";
		return shader;
	}
	Mesh* D3D11GraphicsFactory::CreateMesh(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount)
	{
		ID3D11Buffer* vb;
		ID3D11Buffer* ib;
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		D3D11_SUBRESOURCE_DATA sr_data = { 0 };
		bufferDesc.ByteWidth = sizeof(Vertex) * verticesCount;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		sr_data.pSysMem = vertices;
		sr_data.SysMemPitch = 0;
		sr_data.SysMemSlicePitch = 0;
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
	case DEngine::INPUT_FORMAT::float32_1:
		return DXGI_FORMAT_R32_FLOAT;
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