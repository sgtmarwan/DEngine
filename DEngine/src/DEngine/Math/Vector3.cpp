#include <cmath>
#include "Math/Vector3.h"
namespace DEngine
{

	const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, 1.0f);;


	Vector3::Vector3(float _x, float _y, float _z) : 
		x(_x), y(_y), z(_z)
	{

	}

	Vector3::Vector3(float value) :
		x(value), y(value), z(value)
	{

	}

	float Vector3::DotProduct(const Vector3& vec1, const Vector3& vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	}


	Vector3 Vector3::operator*(const Vector3& vec) const
	{
		return Vector3((y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x));
	}

	Vector3 Vector3::operator*(const float& value) const
	{
		return Vector3(x * value, y * value, z * value);
	}

	Vector3 Vector3::operator-(const Vector3& vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 Vector3::operator+(const Vector3& vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3 Vector3::operator+=(const Vector3& vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	float Vector3::Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector3 Vector3::Normalize(const Vector3& vec)
	{
		float legnth = vec.Length();
		return Vector3(vec.x / legnth, vec.y / legnth, vec.z / legnth);
	}

	void Vector3::Normalize()
	{
		float legnth = Length();
		x /= legnth;
		y /= legnth;
		z /= legnth;
	}
}