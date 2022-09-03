#pragma once
#include "DEngineAPI.h"
#include "Vector3.h"
namespace DEngine
{
	struct DEAPI Vector4
	{
	public:
		float x, y, z, w;
	public:
		Vector4() = default;
		Vector4(float _x, float _y, float _z, float _w);
		Vector4(float value);
		Vector4(const Vector3& vec);
	
		Vector4 operator- (const Vector4& vec) const;
		Vector4 operator+ (const Vector4& vec) const;
		Vector4 operator+= (const Vector4& vec) const;

		void Normalize();
		float Length() const;


	public:
		static float DotProduct(const Vector4& vec1, const Vector4& vec2);
		static Vector4 Normalize(const Vector4& vec);
	};
}