#pragma once
#include "GameObject.h"

namespace GameEngine
{
	enum class Event;
	class GameObject;

	class BaseComponent
	{
	public:
		virtual void Update() {};

		virtual void Render(){};
		virtual ~BaseComponent() {};

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		// should be inherited 
		bool IsDestroyed() const
		{
			return m_IsDestroyed;
		}
		void SetIsDestroyed(bool isDestroyed)
		{
			m_IsDestroyed = isDestroyed;
		}
			
	protected:
		BaseComponent(GameObject* GOptr) :m_GameObject(GOptr), m_IsDestroyed(false){};

		GameObject* GetGameObject() const
		{
			return m_GameObject;

		}

	
	private:
		GameObject* m_GameObject;
		bool m_IsDestroyed;
	};
}




