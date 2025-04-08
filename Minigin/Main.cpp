#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "steam_api.h"

#include <filesystem>

#include "FPSComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include <Commands.h>

#include "Achievements.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "PointDisplayComponent.h"
#include "PointsComponent.h"
#include "SDLAudio.h"
#include "ServiceLocator.h"
#include "SteamAchievements.h"

namespace fs = std::filesystem;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	ServiceLocator::ProvideAudio(std::make_unique<SDLAudio>());

	auto& soundService = ServiceLocator::GetAudio();

	std::string BoomSFX = "BoomSfx";
	soundService.AddSound(BoomSFX, -1, "boom.wav");
	soundService.PlaySound(BoomSFX);

	auto go = std::make_shared<dae::GameObject>("BackgroundGOBJ");
	go->AddComponent<ImageComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("LogoGOBJ");
	go->AddComponent<ImageComponent>("logo.tga");
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("TextGOBJ");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("FPSGOBJ");
	go->AddComponent<TextComponent>("0", font);
	go->AddComponent<FPSComponent>();
	go->SetLocalPosition(0, 0);
	scene.Add(go);

	auto pacman = std::make_shared<dae::GameObject>("PacMan");
	pacman->AddComponent<ImageComponent>("PacMan.png");
	pacman->AddComponent<HealthComponent>(3.f);
	pacman->AddComponent<PointsComponent>();
	pacman->SetLocalPosition(250, 250);
	scene.Add(pacman);

	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadUp },KeyState::Down, 0.f, -500.0f,  pacman.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadDown }, KeyState::Down, 0.f, 500.0f,pacman.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadLeft }, KeyState::Down, -500.0f, 0.f,pacman.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadRight }, KeyState::Down, 500.0f, 0.f,pacman.get());
	dae::InputManager::GetInstance().AddInputMapping<AddHealthCommand>({}, { GamePad_X }, Pressed, -1.f, pacman->GetComponent<HealthComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({}, { GamePad_A }, Pressed, 10.f, pacman->GetComponent<PointsComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({}, { GamePad_B }, Pressed, 100.f, pacman->GetComponent<PointsComponent>());


	auto msPacMan = std::make_shared<dae::GameObject>("MsPacMan");
	msPacMan->AddComponent<ImageComponent>("MsPacMan.png");
	msPacMan->AddComponent<HealthComponent>(3.f);
	msPacMan->AddComponent<PointsComponent>();
	msPacMan->SetLocalPosition(300, 250);
	scene.Add(msPacMan);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	go = std::make_shared<dae::GameObject>("MsPacManLives");
	go->SetLocalPosition(10, 175);
	go->AddComponent<TextComponent>("# lives: 3", font);
	go->AddComponent<HealthDisplayComponent>(msPacMan.get());
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("MsPacmanPoints");
	go->SetLocalPosition(10, 200);
	go->AddComponent<TextComponent>("Score: 0", font);
	go->AddComponent<PointDisplayComponent>(msPacMan.get());
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("PacManLives");
	go->SetLocalPosition(10, 125);
	go->AddComponent<TextComponent>("# lives: 3", font);
	go->AddComponent<HealthDisplayComponent>(pacman.get());
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("PacmanPoints");
	go->SetLocalPosition(10, 150);
	go->AddComponent<TextComponent>("Score: 0", font);
	go->AddComponent<PointDisplayComponent>(pacman.get());
	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	go = std::make_shared<dae::GameObject>("Explanation Text Pacman");
	go->SetLocalPosition(10, 70);
	go->AddComponent<TextComponent>("Use the D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets", font);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("Explanation Text MsPacMan");
	go->SetLocalPosition(10, 95);
	go->AddComponent<TextComponent>("Use the WASD to move MsPacman, C to inflict damage, Z and X to pick up pellets", font);
	scene.Add(go);


	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({SDL_SCANCODE_W}, {}, Down,0.f, -250.0f,msPacMan.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({SDL_SCANCODE_S}, {}, Down,0.f, 250.0f,msPacMan.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({SDL_SCANCODE_A}, {}, Down,-250.0f, 0.f,msPacMan.get());
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({SDL_SCANCODE_D}, {}, Down,250.0f, 0.f,msPacMan.get());
	dae::InputManager::GetInstance().AddInputMapping<AddHealthCommand>({ SDL_SCANCODE_C }, {}, Pressed, -1.f, msPacMan->GetComponent<HealthComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_Z }, {}, Pressed, 10.f, msPacMan->GetComponent<PointsComponent>());
	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({ SDL_SCANCODE_X }, {}, Pressed, 100.f, msPacMan->GetComponent<PointsComponent>());

	Achievements::GetInstance().NotifyAchievements();
}

int main(int, char*[]) {
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
