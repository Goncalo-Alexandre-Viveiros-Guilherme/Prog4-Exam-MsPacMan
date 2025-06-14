#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "steam_api.h"

#include "MsPacmanCode.h"
#include <filesystem>

#include "GameObject.h"
#include "InputManager.h"
#include "MenuController.h"
#include "ResourceManager.h"
#include "SteamAchievements.h"
#include "TextComponent.h"
#include "Commands.h"

namespace fs = std::filesystem;

void load()
{
	dae::Scene* scene = dae::SceneManager::GetInstance().CreateScene("MainMenuScene");

	auto go = std::make_unique<dae::GameObject>("Menu");

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	// Create text components
	auto normalText = go->AddComponent<TextComponent>("Normal", font);
	auto versusText = go->AddComponent<TextComponent>("Versus", font, glm::vec2(0, 100));
	auto coopText = go->AddComponent<TextComponent>("Co-op", font, glm::vec2(0, 200));

	// Create menu controller
	auto menuController = go->AddComponent<MenuController>(normalText, versusText, coopText);

	go->SetLocalPosition((672 / 2) - 50, 794 / 2);
	scene->Add(std::move(go));

	// Add input commands
	auto& input = dae::InputManager::GetInstance();
	input.AddInputMapping<MenuMoveUpCommand>(
		{ SDL_SCANCODE_UP, SDL_SCANCODE_W },
		{ GamePad_DPadUp },
		KeyState::KeyPressed,
		menuController
	);

	input.AddInputMapping<MenuMoveDownCommand>(
		{ SDL_SCANCODE_DOWN, SDL_SCANCODE_S },
		{ GamePad_DPadDown },
		KeyState::KeyPressed,
		menuController
	);

	input.AddInputMapping<MenuSelectCommand>(
		{ SDL_SCANCODE_RETURN, SDL_SCANCODE_SPACE },
		{ GamePad_A },
		KeyState::KeyPressed,
		menuController
	);

	dae::SceneManager::GetInstance().QueueSceneChange(scene);
}

int main(int, char*[])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	if (SteamAPI_Init())
	{
		g_SteamAchievements = std::make_unique<CSteamAchievements>(g_Achievements, 4);
	}

	dae::Minigin engine(data_location);
	engine.Run(load);

	SteamAPI_Shutdown();
	return 0;
}
