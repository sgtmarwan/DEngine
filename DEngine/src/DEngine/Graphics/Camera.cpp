#include "Camera.h"
#include <cmath>

namespace DEngine
{

	Camera::Camera(ProjectionMode mode, int _width, int _height, float _fov, float zNear, float zFar) :
		Fov(_fov), ZNear(zNear), ZFar(zFar)
	{
		AspectRatio = float(_height) / _width;
		fTan = tan(Fov / 2.0f);;
		ProjectionMatrix = Matrix4x4::PrespectiveProjection(AspectRatio, Fov, ZNear, ZFar);
	}

	void Camera::SetRes(int width, int height)
	{
		AspectRatio = float(height) / width;

		ProjectionMatrix[0][0] = fTan * AspectRatio;
	}
	void Camera::SetZ(const float& znear, const float& zfar)
	{
		ZFar = zfar;
		ZNear = znear;
		const float zFac = ZFar / (ZFar - ZNear);
		ProjectionMatrix[2][2] = zFac;
		ProjectionMatrix[3][2] = (zFac - ZNear) * -1.0f;
	}
	void Camera::SetFov(const float& fov)
	{
		Fov = fov;
		fTan = tan(Fov / 2.0f);
		ProjectionMatrix[0][0] = fTan * AspectRatio;
		ProjectionMatrix[1][1] = fTan;
	}
}