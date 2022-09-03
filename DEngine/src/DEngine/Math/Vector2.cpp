#include <cmath>
#include "Math/Vector2.h"
namespace DEngine
{

	const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
	const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);


	Vector2::Vector2(float _x, float _y) : 
		x(_x), y(_y)
	{

	}

	Vector2::Vector2(float value) :
		x(value), y(value)
	{

	}

	float Vector2::DotProduct(const Vector2& vec1, const Vector2& vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y);
	}

	Vector2 Vector2::operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 Vector2::operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 Vector2::operator+=(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	float Vector2::Length() const
	{
		return sqrt((x * x) + (y * y));
	}

	Vector2 Vector2::Normalize(const Vector2& vec)
	{
		float legnth = vec.Length();
		return Vector2(vec.x / legnth, vec.y / legnth);
	}

	void Vector2::Normalize()
	{
		float legnth = Length();
		x /= legnth;
		y /= legnth;
	}
}