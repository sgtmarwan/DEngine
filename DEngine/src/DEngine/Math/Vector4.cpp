#include <cmath>
#include "Math/Vector4.h"
namespace DEngine
{


	Vector4::Vector4(float _x, float _y, float _z, float _w) : 
		x(_x), y(_y), z(_z), w(_w)
	{

	}

	Vector4::Vector4(const Vector3& vec) : 
		x(vec.x), y(vec.y), z(vec.z)
	{

	}

	Vector4::Vector4(float value) :
		x(value), y(value), z(value), w(value)
	{

	}

	float Vector4::DotProduct(const Vector4& vec1, const Vector4& vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z) + (vec1.w * vec2.w);
	}


	Vector4 Vector4::operator-(const Vector4& vec) const
	{
		return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	Vector4 Vector4::operator+(const Vector4& vec) const
	{
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	Vector4 Vector4::operator+=(const Vector4& vec) const
	{
		return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	float Vector4::Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	Vector4 Vector4::Normalize(const Vector4& vec)
	{
		float length = vec.Length();
		return Vector4(vec.x / length, vec.y / length, vec.z / length, vec.w / length);
	}

	void Vector4::Normalize()
	{
		float legnth = Length();
		x /= legnth;
		y /= legnth;
		z /= legnth;
		w /= legnth;
	}
}