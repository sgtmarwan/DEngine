#pragma once
#include "DEngineAPI.h"
namespace DEngine
{
	struct DEAPI Vector2
	{
		public:
		float x, y;
	public:
		Vector2() = default;
		Vector2(float _x, float _y);
		Vector2(float value);

		Vector2 operator- (const Vector2& vec) const;
		Vector2 operator+ (const Vector2& vec) const;
		Vector2 operator+= (const Vector2& vec) const;

		void Normalize();
		float Length() const;

	public:
		static const Vector2 Up;
		static const Vector2 Right;

	public:
		static float DotProduct(const Vector2& vec1, const Vector2& vec2);
		static Vector2 Normalize(const Vector2& vec);
	};
}