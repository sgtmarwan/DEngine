#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include <vector>
namespace DEngine
{
	class Transform
	{
	private:
		Vector3 Position;
		Vector3 WorldPosition;
		Vector3 WorldScale;
		Vector3 Size;
		Quaternion Rotation;
		//void worldPos();
		//void worldScale();
		bool isDirty = true;
	public:
		Transform(const Vector3& pos, const Vector3& scale, const Quaternion& rot);
		void SetPosition(const Vector3& pos);
		void TranslatePosition(const Vector3& translation);
		void Rotate(const Quaternion& rotation);
		void SetRotation(const Quaternion& rotation);
		void Scale(const Vector3& scale);
		void SetScale(const Vector3& scale);
		Vector3 GetPosition() const { return Position; };
		Vector3 GetScale() const { return Size; };
		Vector3 GetWorldPosition() const { return WorldPosition; };
		Vector3 GetWorldScale() const { return WorldScale; };
		Quaternion GetRotation() const { return Rotation; };


		bool IsDirty() { return isDirty; }
	};
}

