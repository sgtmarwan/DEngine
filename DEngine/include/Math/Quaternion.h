#pragma once
#include "Vector4.h"
#include "Vector3.h"

namespace DEngine
{
	class Quaternion
	{
	public:
		float x, y, z, w;
	public:
		Quaternion() = default;
		Quaternion(const Vector3& vec, const float& angle);
		Quaternion(float _x, float _y, float _z, float _w);
		Quaternion(const Vector4& quat);
		Quaternion operator*(const Quaternion& quat) const;
		void operator*=(const Quaternion& quat);
		Quaternion operator-() const;
		Quaternion operator*(const Vector3& vec) const;
		Vector3 Rotate(const Vector3& vec) const;
		float Length() const;
		void Normalize();
		Quaternion Conjugate() const;
		Quaternion Normalized() const;
	public:
		static Quaternion FromEulerAngle(const Vector3& eulerAngle);
		static Quaternion Normalize(const Quaternion& quat);
	};
}