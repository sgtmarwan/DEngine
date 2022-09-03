#include <cmath>
#include "Math/Quaternion.h"
namespace DEngine
{

	Quaternion::Quaternion(const Vector3& vec, const float& angle) : 
		Quat(Vector3::Normalize(vec) * sin(angle / 2))
	{
		Quat.w = cos(angle / 2);
		Quat.Normalize();
	}
	Quaternion::Quaternion(const Vector4& quat) : 
		Quat(Vector4::Normalize(quat))
	{

	}
}