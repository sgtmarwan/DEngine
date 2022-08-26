#include "Mesh.h"

namespace DEngine
{
	Mesh::Mesh(unsigned int ic) : 
		IndicesCount(ic)
	{

	}

	unsigned int Mesh::GetIndicesCount()
	{
		return IndicesCount;
	}
}