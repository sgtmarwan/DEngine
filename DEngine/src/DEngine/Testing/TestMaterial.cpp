#include "TestMaterial.h"

#include "DEngine.h"
#include "Platform/Direct3D11/D3D11Shader.h"
#include "Platform/Direct3D11/D3D11Texture2D.h"

namespace DEngine
{
	Shader* TestMaterial::shader = nullptr;

	void TestMaterial::SetShader(Shader* sh)
	{
		shader = sh;
	}
	Shader* TestMaterial::GetShader()
	{
		return shader;
	}
	TestMaterial::TestMaterial(const MVP& _mvp, const void* _texture, unsigned int width, unsigned int height, TEXTURE2D_FOMAT format)
	{
		mvp = graphicsFactory->CreateShaderData((void*)&_mvp, sizeof(MVP), DATA_USAGE::GR_CW);
		texture = graphicsFactory->CreateTexture2D(_texture, width, height, format, DATA_USAGE::GRW, 0);
		smpl = graphicsFactory->CreateSampler();
	}
	void TestMaterial::Bind()
	{
		shader->Bind();
		mvp->VSSet(0);
		texture->PSSet(0);
		smpl->PSSet(0);
	}

	void TestMaterial::SetMVP(const MVP& _mvp)
	{
		memcpy(mvp->GetDataPointer(true), &_mvp, sizeof(MVP));
		mvp->ReleaseDataPointer();
	}
}

