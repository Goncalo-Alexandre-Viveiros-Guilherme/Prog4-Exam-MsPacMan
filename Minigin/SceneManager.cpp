#include "SceneManager.h"

#include <stdexcept>

#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::FindSceneByName(std::string name) const
{
	for (const auto& scene:m_scenes)
	{
		if (scene->GetName() == name)
		{
			return scene;
		}
	}

	throw std::runtime_error("No scene with that name found");
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
