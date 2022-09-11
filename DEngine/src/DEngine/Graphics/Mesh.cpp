#include "Mesh.h"

namespace DEngine
{
	Mesh::Mesh(VertexBuffer* vb, unsigned int ic) :
		IndicesCount(ic), VB(vb)
	{

	}

	unsigned int Mesh::GetIndicesCount()
	{
		return IndicesCount;
	}

	void Mesh::VBUpdateData(void* data, unsigned int size, unsigned int offset)
	{
		VB->UpdateData(data, size, offset);
	}
	void* Mesh::VBGetDataPointer(bool wait) const
	{
		return VB->GetDataPointer(wait);
	}
	void Mesh::VBReleaseDataPointer() const
	{
		VB->ReleaseDataPointer();
	}
}