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
				if (col == row)
				{
					matrix[col][row] = value;
					continue;
				}
				matrix[col][row] = 0.0f;
			}
		}
	}


	Matrix4x4 Matrix4x4::Rotate(const float& angle, Vector3 rotationAxis)
	{
		float const a = angle;
		float const c = cos(a);
		float const s = sin(a);

		Vector3 axis = Vector3::Normalize( rotationAxis );
		Vector3 temp(rotationAxis * (1.0f - c));

		Matrix4x4 out;
		out[0][0] = c + temp.x * axis.x;
		out[0][1] = temp.x * axis.y + s * axis.z;
		out[0][2] = temp.x * axis.z - s * axis.y;
		out[0][3] = 0.0f;
		
		out[1][0] = temp.y * axis.x - s * axis.z;
		out[1][1] = c + temp.y * axis.y;
		out[1][2] = temp.y * axis.z + s * axis.x;
		out[1][3] = 0.0f;
		
		out[2][0] = temp.z * axis.x + s * axis.y;
		out[2][1] = temp.z * axis.y - s * axis.x;
		out[2][2] = c + temp.z * axis.z;
		out[2][3] = 0.0f;
		
		out[3][0] = 0.0f;
		out[3][1] = 0.0f;
		out[3][2] = 0.0f;
		out[3][3] = 1.0f;

		return out;
	}



	Matrix4x4 Matrix4x4::Rotate(const Quaternion& quat)
	{
		Matrix4x4 out = Matrix4x4();

		float x2 = quat.x * quat.x; 
		float y2 = quat.y * quat.y; 
		float z2 = quat.z * quat.z; 
		float xy = quat.x * quat.y; 
		float xz = quat.x * quat.z; 
		float yz = quat.y * quat.z; 
		float wx = quat.w * quat.x; 
		float wy = quat.w * quat.y;
		float wz = quat.w * quat.z;



		out[0][0] = 1.0f - 2.0f * (y2 + z2);
		out[0][1] = 2.0f * (xy + wz);
		out[0][2] = 2.0f * (xz - wy);
		out[0][3] = 0;

		out[1][0] = 2.0f * (xy - wz);
		out[1][1] = 1.0f - 2.0f * (x2 + z2);
		out[1][2] = 2.0f * (yz + wx);
		out[1][3] = 0;

		out[2][0] = 2.0f * (xz + wy);
		out[2][1] = 2.0f * (yz - wx);
		out[2][2] = 1.0f - 2.0f * (x2 + y2);
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


	Matrix4x4 Matrix4x4::View(const Vector3& position, const Quaternion& rotation)
	{
		return Rotate(-rotation) * Translate(-position);
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