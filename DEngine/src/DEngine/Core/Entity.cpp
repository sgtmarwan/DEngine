#include "Entity.h"

namespace DEngine
{
    void Entity::Start()
    {
    }

    void Entity::Update()
    {
    }

    void Entity::AddChild(Entity* child)
    {
    }

    void Entity::RemoveChild(unsigned int childIndex)
    {
    }

    void Entity::SetParent(Entity* parent)
    {
    }

    void Entity::AddComponent(Component* component)
    {
    }

    void Entity::RemoveComponent(unsigned int componentIndex)
    {
    }

    const std::list<Entity*>& Entity::GetChilds()
    {
        return Childs;
    }
}
