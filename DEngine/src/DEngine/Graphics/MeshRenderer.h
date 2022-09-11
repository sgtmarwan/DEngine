#pragma once
#include "Renderer.h"
#include "MeshData.h"
#include "Material.h"
#include "DEngine/Core/Entity.h"
#include "DEngine/Core/Component.h"
#include "Math/Matrix4x4.h"
namespace DEngine
{
	class MeshRenderer : private  Component
	{
	private:
		MeshData* mesh;
		Material* material;
		Matrix4x4 modelMatrix;
		bool mmUpdated = false;
		void Update() override;
	public:
		MeshRenderer(Entity* e, MeshData* mh, Material* mat);
	};
}

