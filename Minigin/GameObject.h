#pragma once
#include "Components.h"
#include <memory>
#include <vector>
#include <algorithm>

namespace dae
{
	class Texture2D;
	class Component;
	class TextureComponent;
	class TransformComponent;
	class RenderComponent;

	class GameObject final
	{
	public:
		//virtual void Update(float elapsedTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);         
		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

			std::unique_ptr<T> newComponent = std::make_unique<T>(std::forward<Args>(args)...);
			T& componentRef = *newComponent;

			m_Components.push_back(std::move(newComponent));

			return componentRef;
		}


		template <typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
			m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
				[](const auto& component) { return dynamic_cast<T*>(component.get()) != nullptr; }),
				m_Components.end());
		}

		template <typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
			for (const auto& component : m_Components)
			{
				if (auto castedComponent = dynamic_cast<T*>(component.get()))
					return castedComponent;
			}
			return nullptr;
		}

		template <typename T>
		bool HasComponent() const
		{
			static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
			return std::any_of(m_Components.begin(), m_Components.end(),
				[](const auto& component) { return dynamic_cast<T*>(component.get()) != nullptr; });
		}

	private:
		
		std::vector<std::unique_ptr<Component>> m_Components; 
		
		std::unique_ptr<TransformComponent>m_TransformComponent;
		std::unique_ptr<TextureComponent>m_TextureComponent;
		std::unique_ptr<RenderComponent>m_RenderComponent;
	};
}
