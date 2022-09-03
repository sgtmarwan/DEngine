#include "Camera.h"

namespace DEngine
{

	Camera::Camera(const Vector3& pos, const Quaternion& orien) :
		transform(pos, orien)
	{

	}


	void Camera::SetPosition(const Vector3& pos)
	{
		transform.Position = pos;

		ViewMatrix[3][0] = transform.Position.x;
		ViewMatrix[3][1] = transform.Position.y;
		ViewMatrix[3][2] = transform.Position.z;
	}
	void Camera::TranslatePosition(const Vector3& translation)
	{
		transform.Position += translation;

		ViewMatrix[3][0] = transform.Position.x;
		ViewMatrix[3][1] = transform.Position.y;
		ViewMatrix[3][2] = transform.Position.z;
	}
	Matrix4x4 Camera::GetViewMatrix()
	{
		return ViewMatrix;
	}
}