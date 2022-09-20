#pragma once
#include "DEngine/Graphics/Material.h"
#include "Math/Matrix4x4.h"
#include "DEngine/Graphics/Texture2D.h"
#include "DEngine/Graphics/Buffer.h"
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
		Buffer* mvp;
		Texture2D* texture;
		Sampler* smpl;
	public:
		TestMaterial(const MVP& _mvp, const void* _texture, unsigned int width, unsigned int height, TEXTURE2D_FORMAT format);
		virtual ~TestMaterial() = default;
		static void SetShader(Shader* sh);
		unsigned int GetShaderId() override;

		void Bind();
		void SetMVP(const MVP& _mvp);
	};
}

