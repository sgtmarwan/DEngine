#pragma once
#include "DEngineAPI.h"

namespace DEngine
{
	struct DEAPI Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3() = default;
		Vector3(float _x, float _y, float _z);
		Vector3(float value);

		Vector3 operator* (const Vector3& vec) const;
		Vector3 operator* (const float& value) const;
		Vector3 operator- (const Vector3& vec) const;
		Vector3 operator+ (const Vector3& vec) const;
		Vector3 operator+= (const Vector3& vec) const;

		void Normalize();
		float Length() const;

	public:
		static const Vector3 Up;
		static const Vector3 Right;
		static const Vector3 Forward;

	public:
		static float DotProduct(const Vector3& vec1, const Vector3& vec2);
		static Vector3 Normalize(const Vector3& vec);
	};
}