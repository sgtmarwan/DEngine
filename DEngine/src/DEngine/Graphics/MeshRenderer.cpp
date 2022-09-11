#include "MeshRenderer.h"

namespace DEngine
{
	void MeshRenderer::Update()
	{
	}

	void OnTranformDirty(void* mmUpdated)
	{
		bool* u = (bool*)mmUpdated;
		*u = false;
	}

	MeshRenderer::MeshRenderer(Entity* e, MeshData* mh, Material* mat) : 
		Component(e), mesh(mh), material(mat)
	{
		entity->transform.AddDirtyCallback(&OnTranformDirty, &mmUpdated);
	}
}
