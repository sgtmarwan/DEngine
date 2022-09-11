#include <cmath>
#include "Math/Quaternion.h"
namespace DEngine
{

	Quaternion::Quaternion(const Vector3& vec, const float& angle)
	{
		Vector3 vec3 = Vector3::Normalize(vec) * sinf(angle / 2);
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
		w = cosf(angle / 2);
	}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{
		
	}

	Quaternion::Quaternion(const Vector4& quat) : 
		x(quat.x), y(quat.y), z(quat.z), w(quat.w)
	{
	}
	Quaternion Quaternion::operator*(const Quaternion& quat) const
	{
		return Quaternion(
			(((w * quat.x) + (x * quat.w)) + (y * quat.z)) - (z * quat.y),
			(((w * quat.y) + (y * quat.w)) + (z * quat.x)) - (x * quat.z),
			(((w * quat.z) + (z * quat.w)) + (x * quat.y)) - (y * quat.x),
			(((w * quat.w) - (x * quat.x)) - (y * quat.y)) - (z * quat.z)
		);
	}
	void Quaternion::operator*=(const Quaternion& quat)
	{
		x = (((w * quat.x) + (x * quat.w)) + (y * quat.z)) - (z * quat.y);
		y = (((w * quat.y) + (y * quat.w)) + (z * quat.x)) - (x * quat.z);
		z = (((w * quat.z) + (z * quat.w)) + (x * quat.y)) - (y * quat.x);
		w = (((w * quat.w) - (x * quat.x)) - (y * quat.y)) - (z * quat.z);
	}
	Quaternion Quaternion::operator*(const Vector3& vec) const
	{
		return *this * Quaternion(vec.x, vec.y, vec.z, 0.0f);
	}
	Quaternion Quaternion::operator-() const
	{
		return Quaternion(x, y, z, -w);
	}

	Vector3 Quaternion::Rotate(const Vector3& vec) const
	{
		Quaternion quat = *this * Quaternion(vec.x, vec.y, vec.z, 0.0f) * this->Conjugate();
		return Vector3(quat.x, quat.y, quat.z);
	}
	float Quaternion::Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}
	void Quaternion::Normalize()
	{
		float legnth = Length();
		x /= legnth;
		y /= legnth;
		z /= legnth;
		w /= legnth;
	}
	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::FromEulerAngle(const Vector3& eulerAngle)
	{
		Quaternion pitch(Vector3(1.0f, 0.0f, 0.0f), eulerAngle.x);
		Quaternion yaw(Vector3(0.0f, 1.0f, 0.0f), eulerAngle.y);
		Quaternion roll(Vector3(0.0f, 0.0f, 1.0f), eulerAngle.z);
		return pitch * yaw * roll;
	}

	Quaternion Quaternion::Normalize(const Quaternion& quat)
	{
		float legnth = quat.Length();
		return Quaternion(quat.x / legnth, quat.y / legnth, quat.z / legnth, quat.w / legnth);
	}

	Quaternion Quaternion::Normalized() const
	{
		float s = sinf(acosf(w));
		Vector3 vec = Vector3::Normalize(Vector3(x, y, z) / s) * s;
		return Quaternion(vec.x, vec.y, vec.z, w);
	}
}