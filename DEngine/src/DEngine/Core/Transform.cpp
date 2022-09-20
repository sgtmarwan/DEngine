#include "Transform.h"

#include "Entity.h"
namespace DEngine
{
	
	Transform::Transform(const Vector3& pos, const Vector3& scale, const Quaternion& rot) :
		Position(pos), Size(scale), Rotation(rot)
	{
		
	}

	/*void Transform::worldPos()
	{
		WorldPosition = entity->GetParent()->transform.GetWorldPosition() + Position;
	}
	void Transform::worldScale()
	{
		WorldScale = entity->GetParent()->transform.GetWorldScale() + Size;
	}*/


	void Transform::SetPosition(const Vector3& pos)
	{
		Position = pos;
		//worldPos();
		isDirty = true;
	}
	void Transform::TranslatePosition(const Vector3& translation)
	{
		Position += translation;
		//worldPos();
		isDirty = true;
	}
	void Transform::Rotate(const Quaternion& rotation)
	{
		Rotation *= rotation;
	}
	void Transform::SetRotation(const Quaternion& rotation)
	{
		Rotation = rotation;
	}
	void Transform::Scale(const Vector3& scale)
	{
		Size += scale;
		//worldScale();
		isDirty = true;
	}
	void Transform::SetScale(const Vector3& scale)
	{
		Size = scale;
		//worldScale();
		isDirty = true;
	}
}