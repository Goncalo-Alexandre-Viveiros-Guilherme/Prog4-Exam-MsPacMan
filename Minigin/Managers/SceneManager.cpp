#include "SceneManager.h"

#include <stdexcept>

#include "EventDispatcher.h"
#include "InputManager.h"
#include "Scene.h"
#include "ServiceLocator.h"

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

dae::Scene* dae::SceneManager::FindSceneByName(const std::string& name) const
{
	for (const auto& scene:m_Scenes)
	{
		if (scene->GetName() == name)
		{
			return scene.get();
		}
	}

	throw std::runtime_error("No scene with that name found");
}

void dae::SceneManager::PrepManagers()
{
	dae::InputManager::GetInstance().ClearMappings();
	ServiceLocator::GetAudioService().Clear();
	ServiceLocator::GetCollisionService().Clear();
	EventDispatcher::GetInstance().Clear();
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return scene.get();
}
