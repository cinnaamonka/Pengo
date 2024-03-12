#pragma once
#include "Singleton.h"

#include <string>
#include <memory>
#include <vector>

namespace GameEngine
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();

		void Cleanup();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		// one scene needed 
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
