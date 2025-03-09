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

#include <filesystem>

#include "GraphCacheComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include "RotatorComponent.h"
#include "TextComponent.h"
#include <Commands.h>
#include "InputManager.h"
namespace fs = std::filesystem;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>("BackgroundGOBJ");
	go->AddComponent<ImageComponent>();
	go->GetComponent<ImageComponent>().SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("LogoGOBJ");
	go->AddComponent<ImageComponent>();
	go->GetComponent<ImageComponent>().SetTexture("logo.tga");
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

	go = std::make_shared<dae::GameObject>("PacMan");
	go->AddComponent<ImageComponent>();
	go->GetComponent<ImageComponent>().SetTexture("PacMan.png");
	go->SetLocalPosition(250, 250);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>("MsPacMan");
	go->AddComponent<ImageComponent>();
	go->SetLocalPosition(300, 250);
	go->GetComponent<ImageComponent>().SetTexture("MsPacMan.png"); 
	scene.Add(go);

	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_W }, dae::KeyState::Pressed, 0.f,-500.0f);
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_S }, dae::KeyState::Pressed, 0.f,500.0f);
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_A }, dae::KeyState::Pressed, -500.0f, 0.f);
	dae::InputManager::GetInstance().AddInputMapping<MoveCommand>({ SDL_SCANCODE_D }, dae::KeyState::Pressed, 500.0f, 0.f);

	dae::InputManager::GetInstance().AddPlayer(go.get());
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
