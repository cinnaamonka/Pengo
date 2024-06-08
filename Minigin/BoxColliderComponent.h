#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

#include <memory>

namespace GameEngine
{
	class GameObject;

	class BoxCollider final :public BaseComponent
	{
	public:
		BoxCollider(GameObject* pGameObject,int left, int bottom, int width, int height); 
		BoxCollider(GameObject* pGameObject,const Rect& shape); 
		~BoxCollider() = default;

		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) = delete;

		Rect& GetBoxCollider()
		{
			return m_RectCollider;
		}
		void SetBoxCollider(const Rect& rect)
		{
			m_RectCollider = rect;
		}
		void SetBoxCollider(const glm::vec3& position)
		{
			m_RectCollider.left = static_cast<int>(position.x);
			m_RectCollider.bottom = static_cast<int>(position.y);
		}

		bool IsCollidingHorizontally(const Rect& rectShape,HitInfo& hitInfo) const;
		bool IsCollidingVertically(const Rect& rectShape, HitInfo& hitInfo) const;

		std::vector<glm::vec3> CreatePointsFromRect(const Rect& rectShape) const;
		
	private:
		Rect m_RectCollider;

	};
}

