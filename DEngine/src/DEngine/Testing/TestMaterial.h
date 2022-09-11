#pragma once
#include "DEngine/Graphics/Material.h"
#include "Math/Matrix4x4.h"
#include "DEngine/Graphics/Texture2D.h"
namespace DEngine
{
	class TestMaterial : public Material
	{
	public:
		struct MVP
		{
			Matrix4x4 mat;
		};
	private:
		static Shader* shader;
		ShaderData* mvp;
		Texture2D* texture;
		Sampler* smpl;
	public:
		TestMaterial(const MVP& _mvp, const void* _texture, unsigned int width, unsigned int height, TEXTURE2D_FOMAT format);
		virtual ~TestMaterial() = default;
		static void SetShader(Shader* sh);
		Shader* GetShader();

		void Bind();
		void SetMVP(const MVP& _mvp);
	};
}

