#pragma once
#include "DEngine/Core/Transform.h"
#include "Math/Matrix4x4.h"

namespace DEngine
{
	class Camera
	{
	private:
		Transform transform;
		Matrix4x4 ViewMatrix;
	public:
		Camera(const Vector3& pos, const Quaternion& orien);
		~Camera() = default;

		void SetPosition(const Vector3& pos);
		void TranslatePosition(const Vector3& translation);
		Matrix4x4 GetViewMatrix();
	};
}