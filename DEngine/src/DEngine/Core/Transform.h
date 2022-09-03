#pragma once

#include "Math/Vector3.h"
#include "Math/Quaternion.h"
namespace DEngine
{
	struct Transform
	{
	public:
		Vector3 Position, Scale;
		Quaternion Orientation;
	public:
		Transform() = default;
		Transform(const Vector3& pos, const Quaternion& orien);
	};
}