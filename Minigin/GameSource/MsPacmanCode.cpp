#include "MsPacmanCode.h"

#include "Achievements.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "ImageComponent.h"
#include "InputManager.h"
#include "MsPacMan.h"
#include "PointDisplayComponent.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"

void MsPacmanCode::InitializeResources()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MsPacman");

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

//	auto pacman = std::make_shared<dae::GameObject>("PacMan");
//	pacman->AddComponent<ImageComponent>("PacMan.png");
//	pacman->AddComponent<MoveComponent>();
//	pacman->AddComponent<HealthComponent>(3.f);
//	pacman->AddComponent<PointsComponent>();
//	pacman->SetLocalPosition(250, 250);
//	scene.Add(pacman);

	MsPacMan msPacMan{scene};

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	go = std::make_shared<dae::GameObject>("MsPacManLives");
	go->SetLocalPosition(10, 175);
	go->AddComponent<TextComponent>("# lives: 3", font);
	go->AddComponent<HealthDisplayComponent>(msPacMan.GetGameObject());
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("MsPacmanPoints");
	go->SetLocalPosition(10, 200);
	go->AddComponent<TextComponent>("Score: 0", font);
	go->AddComponent<PointDisplayComponent>(msPacMan.GetGameObject());
	scene.Add(go);

//	go = std::make_shared<dae::GameObject>("PacManLives");
//	go->SetLocalPosition(10, 125);
//	go->AddComponent<TextComponent>("# lives: 3", font);
//	go->AddComponent<HealthDisplayComponent>(pacman.get());
//	scene.Add(go);
//
//	go = std::make_shared<dae::GameObject>("PacmanPoints");
//	go->SetLocalPosition(10, 150);
//	go->AddComponent<TextComponent>("Score: 0", font);
//	go->AddComponent<PointDisplayComponent>(pacman.get());
//	scene.Add(go);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	go = std::make_shared<dae::GameObject>("Explanation Text Pacman");
	go->SetLocalPosition(10, 70);
	go->AddComponent<TextComponent>("Use the D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets", font);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("Explanation Text MsPacMan");
	go->SetLocalPosition(10, 95);
	go->AddComponent<TextComponent>("Use the WASD to move MsPacman, C to inflict damage, Z and X to pick up pellets", font);
	scene.Add(go);

//	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadUp }, KeyState::Down, 0.f, -500.0f, pacman->GetComponent<MoveComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadDown }, KeyState::Down, 0.f, 500.0f, pacman->GetComponent<MoveComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadLeft }, KeyState::Down, -500.0f, 0.f, pacman->GetComponent<MoveComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({}, { GamePad_DPadRight }, KeyState::Down, 500.0f, 0.f, pacman->GetComponent<MoveComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<AddHealthCommand>({}, { GamePad_X }, Pressed, -1.f, pacman->GetComponent<HealthComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({}, { GamePad_A }, Pressed, 10.f, pacman->GetComponent<PointsComponent>());
//	dae::InputManager::GetInstance().AddInputMapping<AddPointsCommand>({}, { GamePad_B }, Pressed, 100.f, pacman->GetComponent<PointsComponent>());

	Achievements::GetInstance().NotifyAchievements();
}

void MsPacmanCode::LoadGameCode()
{
	InitializeResources();

	auto& soundService = ServiceLocator::GetAudio();

	//	std::string BoomSFX = "BoomSfx";
	//	soundService.AddSound(BoomSFX, -1, "boom.wav");
	//	soundService.PlaySound(BoomSFX,130);

	soundService.AddMusic("skibidi", "Sounds/ms_start.wav");
	soundService.PlayMusic("skibidi", 100, 1);
}
