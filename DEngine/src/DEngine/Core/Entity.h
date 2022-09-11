#pragma once
#include <list>
#include <vector>
#include "Component.h"
#include "Transform.h"
namespace DEngine
{
	class Entity
	{
	public:
		Transform transform;
		void Start();
		void Update();
		Entity* GetParent() { return Parent; }
		void AddChild(Entity* child);
		void RemoveChild(unsigned int childIndex);
		void SetParent(Entity* parent);
		void AddComponent(Component* component);
		void RemoveComponent(unsigned int componentIndex);
		const std::list<Entity*>& GetChilds();
	private:
		Entity* Parent = nullptr;
		unsigned int index;
		std::list<Entity*> Childs;
		std::vector<Component*> Components;
	};
}



