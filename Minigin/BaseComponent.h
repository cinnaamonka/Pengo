#pragma once

#include <memory>
#include <iomanip>

#include "GameObject.h"

class GameObject;

namespace GameEngine
{
	class BaseComponent
	{
	public:
		virtual void Update() {};

		virtual void Render() const {};
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
		BaseComponent(GameObject* GOptr) :m_GameObject(GOptr) {};

		GameObject* GetGameObject() const
		{
			return m_GameObject;
		}
	private:
		GameObject* m_GameObject;
		bool m_IsDestroyed;
	};

	

	

	

	
	

	

}




