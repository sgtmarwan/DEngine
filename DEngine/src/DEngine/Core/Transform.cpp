#include "Transform.h"

#include "Entity.h"
namespace DEngine
{
	void Transform::Update()
	{
		if (isDirty)
		{
			worldPos();
			worldScale();
			isDirty = false;
			for (DC d : dirtyCallbacks)
				d.dc(d.ad);
		}
	}
	Transform::Transform(Entity* e, const Vector3& pos, const Vector3& scale, const Quaternion& rot) :
		Component(e), Position(pos), Size(scale), Rotation(rot)
	{
		
	}

	void Transform::worldPos()
	{
		WorldPosition = entity->GetParent()->transform.GetWorldPosition() + Position;
	}
	void Transform::worldScale()
	{
		WorldScale = entity->GetParent()->transform.GetWorldScale() + Size;
	}

	void Transform::AddDirtyCallback(DirtyCallback callback, void* additionalData)
	{
		DC n;
		n.dc = callback;
		n.ad = additionalData;
		dirtyCallbacks.emplace_back(n);
	}

	void Transform::SetPosition(const Vector3& pos)
	{
		Position = pos;
		worldPos();
		isDirty = true;
	}
	void Transform::TranslatePosition(const Vector3& translation)
	{
		Position += translation;
		worldPos();
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
		worldScale();
		isDirty = true;
	}
	void Transform::SetScale(const Vector3& scale)
	{
		Size = scale;
		worldScale();
		isDirty = true;
	}
}