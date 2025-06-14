#include "SceneManager.h"

#include <stdexcept>

#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::Update() const
{
	m_CurrentScene->Update();
}

void dae::SceneManager::FixedUpdate() const
{
	m_CurrentScene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	m_CurrentScene->Render();
}

void dae::SceneManager::DeleteObjects() const
{
	m_CurrentScene->DeleteObjects();
}

void dae::SceneManager::DeleteScenes()
{
	m_Scenes.clear();
}

void dae::SceneManager::QueueSceneChange(Scene* scene)
{
	m_SceneChangeQueue.push(scene);
}

void dae::SceneManager::PopSceneChangeQueue()
{
	if (!m_SceneChangeQueue.empty())
	{
		m_CurrentScene = m_SceneChangeQueue.back();
		m_SceneChangeQueue.pop();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::FindSceneByName(std::string name) const
{
	for (const auto& scene:m_Scenes)
	{
		if (scene->GetName() == name)
		{
			return scene;
		}
	}

	throw std::runtime_error("No scene with that name found");
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return scene.get();
}
