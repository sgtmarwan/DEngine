#pragma once
#include "Vector4.h"
#include "Vector3.h"

namespace DEngine
{
	class Quaternion
	{
	public:
		Vector4 Quat;
	public:
		Quaternion() = default;
		Quaternion(const Vector3& vec, const float& angle);
		Quaternion(const Vector4& quat);
	};
}