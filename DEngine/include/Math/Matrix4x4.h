#pragma once
#include "Vector3.h"
#include "Quaternion.h"
namespace DEngine
{
	class Matrix4x4
	{
	public:
		struct col
		{
			float row[4];

			float& operator[](int index);
			float operator[](int index) const;
		};
	private:
		col matrix[4];
	public:
		col& operator[](int index);
		col operator[](int index) const;
		Matrix4x4 operator* (const Matrix4x4& mat) const;
		Matrix4x4() = default;
		~Matrix4x4() = default;
		Matrix4x4(float value);


	public:
		static Matrix4x4 Transpose(const Matrix4x4& mat);
		static Matrix4x4 PrespectiveProjection(const float aspectRatio, const float fov, const float zNear, const float zFar);
		static Matrix4x4 View(const Vector3& postion, const Vector3& forward, const Vector3& right, const Vector3& up);
		static Matrix4x4 Transform(const Vector3& translation, const Vector3& scaling);
		static Matrix4x4 Translate(const Vector3& translation);
		static Matrix4x4 Rotate(const Quaternion& quat);
		static Matrix4x4 Scale(const Vector3& scaling);
	};
}