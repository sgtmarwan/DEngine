#pragma once
namespace DEngine
{
	class Entity;
	class Component
	{
	protected:
		Entity* entity;
	public:
		Component(Entity* e);
		virtual ~Component() = default;
		virtual void Start();
		virtual void Update();
	};
}

