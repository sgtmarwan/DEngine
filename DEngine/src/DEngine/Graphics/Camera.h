#pragma once
#include "Math/Matrix4x4.h"

namespace DEngine
{
	enum class ProjectionMode
	{
		Prespective, Orthographic
	};
	class Camera
	{
		Camera() = delete;
	private:
		Matrix4x4 ProjectionMatrix;
		float AspectRatio;
		ProjectionMode Mode;
		float Fov, ZNear, ZFar;
		float fTan;
	public:
		Camera(ProjectionMode mode, int _width, int _height, float _fov, float zNear, float zFar);
		virtual ~Camera() = default;

		void SetRes(int width, int height);
		void SetZ(const float& znear, const float& zfar);
		void SetFov(const float& fov);
		Matrix4x4 GetProjectionMatrix() const { return ProjectionMatrix; }

	};
}