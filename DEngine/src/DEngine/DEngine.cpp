#include "DEngine.h"
#include "Platform/Direct3D11/Direct3D11Context.h"
#include "Platform/Direct3D11/D3D11GraphicsFactory.h"
#include "Platform/Direct3D11/D3D11Mesh.h"
#include "Platform/Direct3D11/D3D11Shader.h"
#include "Platform/Direct3D11/D3D11VertexBuffer.h"
#include "Platform/Direct3D11/D3D11Texture2D.h"

#include "Graphics/Material.h"
namespace DEngine
{
	GraphicsAPI GAPI;

	static void setupDirect3D11(Direct3D11Context* graphicsContext)
	{
		D3D11Mesh::SetGraphicsContext(graphicsContext);
		D3D11Shader::SetGraphicsContext(graphicsContext);
		D3D11ShaderData::SetGraphicsContext(graphicsContext);
		D3D11Texture2D::SetGraphicsContext(graphicsContext);
		D3D11Sampler::SetGraphicsContext(graphicsContext);
		D3D11VertexBuffer::SetGraphicsContext(graphicsContext);
	}
	void SetupGraphicsContext(const GraphicsContext* gc, const GraphicsFactory* gf,GraphicsAPI api)
	{
		Material::SetGraphicsFactory(gf);
		switch (api)
		{
		case DEngine::GraphicsAPI::Direct3D11:
			setupDirect3D11((Direct3D11Context*)gc);
			break;
		default:
			break;
		}
	}
}