#pragma once

#include <string>
#include <memory>
#include <vector>

namespace GameEngine
{
	class GameObject;

	class Scene final
	{
		friend class SceneManager;

	public:
		explicit Scene(const std::string& name);
		void Add(std::unique_ptr<GameObject>&& object);
		void RemoveAll();
		void RemoveObject();

		void Update();
		void Render() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void CleanUp();

	private: 
		

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_pObjects{};

		static unsigned int m_idCounter; 
	};

}
