#pragma once
#include "Singleton.h"

#include <string>
#include <memory>
#include <vector>
#include "Scene.h"

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
		void Destroy();
		void DeleteCurrentScene();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unique_ptr<Scene> m_pCurrentScene;
	};
}
