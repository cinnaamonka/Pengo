#pragma once
#include "Components.h"
#include <memory>
#include <vector>
#include <string>
#include <map>
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
		void Update(float elapsedSec);
		void Render() const;

		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;

		template <typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

			if (GetComponent<T>() == nullptr)
			{
				std::unique_ptr<T> newComponent = std::make_unique<T>(this, std::forward<Args>(args)...);

				m_Components.push_back(std::move(newComponent));
			}
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
		
	};
}
