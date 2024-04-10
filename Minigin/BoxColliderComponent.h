#pragma once
#include "BaseComponent.h"
#include "Helpers.h"
#include "Texture2D.h"

#include <SDL.h>           
#include <SDL_image.h>  
#include <memory>

namespace GameEngine
{
	class GameObject;
	class Texture2D;
	class TextureComponent;

	class BoxCollider final :public BaseComponent
	{
	public:
		BoxCollider(GameObject* pGameObject,int left, int bottom, int width, int height); 
		BoxCollider(GameObject* pGameObject, Rect shape); 
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
		//void Update() override;
	
	private:
		//void CreateTextureFromRect(int width, int height, SDL_Color color);
	private:
		Rect m_RectCollider;
		/*std::unique_ptr<Texture2D> m_pColliderTexture;  

		SDL_Color m_Color = { 255, 255, 255, 255 };

		TextureComponent* m_pTextureComponent; */

	};
}

