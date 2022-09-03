#include "Math/Matrix4x4.h"
#include <cmath>

namespace DEngine
{
	constexpr float PI = 22.0f / 7.0f;
	constexpr float deg2rad = PI / 180.0f;


	Matrix4x4::Matrix4x4(float value)
	{
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				matrix[col][row] = value;
			}
		}
	}

	Matrix4x4 Matrix4x4::Rotate(const Quaternion& quat)
	{
		Matrix4x4 out = Matrix4x4();
		out[0][0] = 1 - 2 * (quat.Quat.y * quat.Quat.y) - 2 * (quat.Quat.z * quat.Quat.z);
		out[0][1] = 2 * (quat.Quat.x * quat.Quat.y) + 2 * (quat.Quat.z * quat.Quat.w);
		out[0][2] = 2 * (quat.Quat.x * quat.Quat.z) + 2 * (quat.Quat.y * quat.Quat.w);
		out[0][3] = 0;

		out[1][0] = 2 * (quat.Quat.x * quat.Quat.y) + 2 * (quat.Quat.z * quat.Quat.w);
		out[1][1] = 1 - 2 * (quat.Quat.x * quat.Quat.x) - 2 * (quat.Quat.z * quat.Quat.z);
		out[1][2] = 2 * (quat.Quat.y * quat.Quat.z) + 2 * (quat.Quat.x * quat.Quat.w);
		out[1][3] = 0;

		out[2][0] = 2 * (quat.Quat.x * quat.Quat.z) + 2 * (quat.Quat.y * quat.Quat.w);
		out[2][1] = 2 * (quat.Quat.y * quat.Quat.z) + 2 * (quat.Quat.x * quat.Quat.w);
		out[2][2] = 1 - 2 * (quat.Quat.x * quat.Quat.x) - 2 * (quat.Quat.y * quat.Quat.y);
		out[2][3] = 0;

		out[3][0] = 0;
		out[3][1] = 0;
		out[3][2] = 0;
		out[3][3] = 1;

		return out;
	}

	Matrix4x4 Matrix4x4::PrespectiveProjection(const float aspectRatio, const float fov, const float zNear, const float zFar)
	{
		const float f = tan(fov / 2.0f);
		const float zFac = zFar / (zFar - zNear);
		Matrix4x4 out(0.0f);
		out[0][0] = f * aspectRatio;
		out[1][1] = f;
		out[2][2] = zFac;
		out[3][2] = (zFac - zNear) * -1.0f;
		out[2][3] = 1.0f;
		return out;
	}

	float& Matrix4x4::col::operator[](int index)
	{
		return row[index];
	}

	Matrix4x4::col& Matrix4x4::operator[](int index)
	{
		return matrix[index];
	}

	float Matrix4x4::col::operator[](int index) const
	{
		return row[index];
	}

	Matrix4x4::col Matrix4x4::operator[](int index) const
	{
		return matrix[index];
	}


	Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& mat)
	{
		Matrix4x4 out;
		for (int cols = 0; cols < 4; cols++)
		{
			for (int rows = 0; rows < 4; rows++)
			{
				out[rows][cols] = mat[cols][rows];
			}
		}
		return out;
	}


	Matrix4x4 Matrix4x4::View(const Vector3& postion, const Vector3& forward, const Vector3& right, const Vector3& up)
	{
		Matrix4x4 out;

		out[0][0] = right.x;
		out[0][1] = right.y;
		out[0][2] = right.z;
		out[0][3] = 0.0f;

		out[1][0] = up.x;
		out[1][1] = up.y;
		out[1][2] = up.z;
		out[1][3] = 0.0f;

		out[2][0] = forward.x;
		out[2][1] = forward.y;
		out[2][2] = forward.z;
		out[2][3] = 0.0f;

		out[3][0] = postion.x;
		out[3][1] = postion.y;
		out[3][2] = postion.z;
		out[3][3] = 1.0f;

		return out;
	}


	Matrix4x4 Matrix4x4::Transform(const Vector3& translation, const Vector3& scaling)
	{
		Matrix4x4 out(0.0f);
		out[0][0] = scaling.x;
		out[1][1] = scaling.y;
		out[2][2] = scaling.z;
		out[3][0] = translation.x;
		out[3][1] = translation.y;
		out[3][2] = translation.z;
		out[3][3] = 1.0f;
		return out;
	}
	Matrix4x4 Matrix4x4::Translate(const Vector3& translation)
	{
		Matrix4x4 out(0.0f);
		out[0][0] = 1.0f;
		out[1][1] = 1.0f;
		out[2][2] = 1.0f;
		out[3][0] = translation.x;
		out[3][1] = translation.y;
		out[3][2] = translation.z;
		out[3][3] = 1.0f;
		return out;
	}

	Matrix4x4 Matrix4x4::Scale(const Vector3& scaling)
	{
		Matrix4x4 out(0.0f);
		out[0][0] = scaling.x;
		out[1][1] = scaling.y;
		out[2][2] = scaling.z;
		out[3][3] = 1.0f;
		return out;
	}


	Matrix4x4 Matrix4x4::operator* (const Matrix4x4& mat) const
	{
		Matrix4x4 out(0.0f);
		for (int col = 0; col < 4; col++)
		{
			for (int row = 0; row < 4; row++)
			{
				out[col][row] = 0.0f;
				for (int i = 0; i < 4; i++)
				{
					out[col][row] += matrix[i][row] * mat[col][i];
				}
			}
		}
		return out;
	}
}