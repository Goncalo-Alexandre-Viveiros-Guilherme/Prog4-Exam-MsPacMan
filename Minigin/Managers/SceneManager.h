#pragma once
#include <vector>
#include <string>
#include <memory>
#include <queue>

#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		dae::Scene* CreateScene(const std::string& name);

		void Update() const;
		void FixedUpdate() const;
		void Render() const;
		void DeleteObjects() const;
		void DeleteScenes();
		void QueueSceneChange(Scene* scene);
		void PopSceneChangeQueue();
		Scene* FindSceneByName(const std::string& name) const;
		void PrepManagers();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::queue<Scene*> m_SceneChangeQueue;
		Scene* m_CurrentScene {nullptr};
	};
}
