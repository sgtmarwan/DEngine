#include <d3dcompiler.h>

#include "D3D11GraphicsFactory.h"
#include "D3D11Shader.h"

DXGI_FORMAT GetInputFormat(DEngine::INPUT_FORMAT format);
D3D11_USAGE GetUsage(DEngine::DATA_USAGE usage);
int GetCPUAccessFlags(DEngine::DATA_USAGE usage);

namespace DEngine
{
	Direct3D11Context* D3D11GraphicsFactory::graphicsContext = nullptr;

	ID3D11VertexShader* D3D11GraphicsFactory::CreateVertexShader(void** VSSources, size_t* VSSize, unsigned int VSCount, ID3DBlob** vs_blob_out)
	{
		ID3D11VertexShader* vs;
		ID3DBlob* vs_blob;
		ID3D11Module* vs_module;
		ID3D11ModuleInstance** vs_modules_instance = new ID3D11ModuleInstance * [VSCount];
		ID3D11Linker* vs_linker;
		D3DCreateLinker(&vs_linker);
		D3DLoadModule(VSSources[0], VSSize[0], &vs_module);
		vs_module->CreateInstance("VS_Entry", &vs_modules_instance[0]);
		vs_module->Release();
		for (int i = 1; i < VSCount; ++i)
		{
			D3DLoadModule(VSSources[i], VSSize[i], &vs_module);
			vs_module->CreateInstance(NULL, &vs_modules_instance[i]);
			vs_linker->UseLibrary(vs_modules_instance[i]);
			vs_module->Release();
		}
		vs_linker->Link(vs_modules_instance[0], "VS_Entry", "VS", NULL, &vs_blob, nullptr);
		graphicsContext->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), NULL, &vs);
		*vs_blob_out = vs_blob;
		vs_linker->Release();
		for (int i = 0; i < VSCount; ++i)
			vs_modules_instance[i]->Release();
		delete[VSCount] vs_modules_instance;
		return vs;
	}
	ShaderData* D3D11GraphicsFactory::CreateShaderData(void** data, size_t* size, unsigned int count, DATA_USAGE usage)
	{
		ID3D11Buffer** buff = new ID3D11Buffer*[count];
		D3D11ShaderData* shaderData = new D3D11ShaderData;
		shaderData->DataCount = count;
		size_t* sizes = new size_t[count];
		D3D11_BUFFER_DESC bd = {};
		for (int i = 0; i < count; ++i)
		{
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.ByteWidth = size[i];
			bd.Usage = GetUsage(usage);
			bd.CPUAccessFlags = GetCPUAccessFlags(usage);
			bd.MiscFlags = 0;
			bd.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA sd = { data[i], 0, 0};
			graphicsContext->GetDevice()->CreateBuffer(&bd, &sd, &buff[i]);
			*sizes = size[i];
		}

		shaderData->Data = buff;
		shaderData->Size = sizes;
		return shaderData;
	}
	ID3D11PixelShader* D3D11GraphicsFactory::CreatePixelShader(void** PSSources, size_t* PSSize, unsigned int PSCount)
	{
		ID3D11PixelShader* ps;
		ID3DBlob* ps_blob;
		ID3D11Module* ps_module;
		ID3D11ModuleInstance** ps_modules_instance = new ID3D11ModuleInstance * [PSCount];
		ID3D11Linker* ps_linker;
		D3DCreateLinker(&ps_linker);
		D3DLoadModule(PSSources[0], PSSize[0], &ps_module);
		ps_module->CreateInstance("PS_Entry", &ps_modules_instance[0]);
		ps_module->Release();
		for (int i = 1; i < PSCount; ++i)
		{
			D3DLoadModule(PSSources[i], PSSize[i], &ps_module);
			ps_module->CreateInstance(NULL, &ps_modules_instance[i]);
			ps_linker->UseLibrary(ps_modules_instance[i]);
			ps_module->Release();
		}
		ps_linker->Link(ps_modules_instance[0], "PS_Entry", "PS", NULL, &ps_blob, nullptr);
		graphicsContext->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), NULL, &ps);
		ps_blob->Release();
		ps_linker->Release();
		for (int i = 0; i < PSCount; ++i)
			ps_modules_instance[i]->Release();
		delete[PSCount] ps_modules_instance;
		return ps;
	}
	ID3D11InputLayout* D3D11GraphicsFactory::CreateInputLayout(INPUT_LAYOUT* inputLayout, unsigned int count, ID3DBlob* vs_blob)
	{
		ID3D11InputLayout* il;
		D3D11_INPUT_ELEMENT_DESC* inputElements = new D3D11_INPUT_ELEMENT_DESC[count];
		for (int i = 0; i < count; ++i)
			inputElements[i] = { inputLayout[i].Name, inputLayout[i].Index, GetInputFormat(inputLayout[i].Format), 0, inputLayout[i].Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		graphicsContext->GetDevice()->CreateInputLayout(inputElements, count, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &il);
		delete[count] inputElements;
		return il;
	}
	Shader* D3D11GraphicsFactory::CreateShader(void** VSSources, size_t* VSSize, unsigned int VSCount, void** PSSources, size_t* PSSize, unsigned int PSCount, INPUT_LAYOUT* inputLayout, unsigned int inputElementsCount)
	{
		ID3DBlob* vs_blob;
		ID3D11VertexShader* vs = CreateVertexShader(VSSources, VSSize, VSCount, &vs_blob);
		ID3D11PixelShader* ps = CreatePixelShader(PSSources, PSSize, PSCount);
		ID3D11InputLayout* il = CreateInputLayout(inputLayout, inputElementsCount, vs_blob);
		vs_blob->Release();
		Shader* shader = new D3D11Shader(vs, ps, il);
		return shader;
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