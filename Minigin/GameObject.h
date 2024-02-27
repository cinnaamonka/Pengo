#pragma once


namespace GameEngine
{
	class BaseComponent;
	

	class GameObject final
	{
	public:
		void Update();
		void Render() const;

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;

		template <typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		void AddComponent(Args&&... args)
		{
			if (GetComponent<ComponentType>() == nullptr)
			{
				std::unique_ptr<ComponentType> newComponent = std::make_unique<ComponentType>(this, std::forward<Args>(args)...);

				m_Components.push_back(std::move(newComponent));
			}
		}

		template <typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		void RemoveComponent()
		{
			m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
				[](const auto& component) { return dynamic_cast<ComponentType*>(component.get()) != nullptr; }),
				m_Components.end());
		}

		template <typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		ComponentType* GetComponent()
		{
			for (const auto& component : m_Components)
			{
				if (auto castedComponent = dynamic_cast<ComponentType*>(component.get()))
					return castedComponent;
			}
			return nullptr;
		}

		template <typename ComponentType, typename... Args>
		requires std::derived_from<ComponentType, BaseComponent>
		bool HasComponent() const
		{
			return std::any_of(m_Components.begin(), m_Components.end(),
				[](const auto& component) { return dynamic_cast<ComponentType*>(component.get()) != nullptr; });
		}

		bool IsDestroyed() const
		{
			return m_IsDestroyed;
		}

		void SetIsDestroyed(bool isDestroyed)
		{
			m_IsDestroyed = isDestroyed;
		}

		void CleanUp();

		void SetParent(GameObject* newParent);
		bool IsValidParent(GameObject* newParent);
		bool IsDescendant(GameObject* potentialParent);
		
		GameObject* GetParent() const
		{
			return m_pParent;
		}

		const std::vector<GameObject*>& GetChildren() const 
		{
			return m_pChildren;
		}

	private:
		
		std::vector<std::unique_ptr<BaseComponent>> m_Components;

		bool m_IsDestroyed;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		
	};
}
