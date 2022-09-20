#pragma once
#include "Math/Vector3.h"
#include "Math/Vector2.h"
namespace DEngine
{
	struct Vertex
	{
		Vector3 Position;
		Vector3 Normal;
		Vector2 TexCoords;
	};
}