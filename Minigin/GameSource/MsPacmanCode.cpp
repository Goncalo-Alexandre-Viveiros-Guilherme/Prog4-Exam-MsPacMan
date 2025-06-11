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

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <iostream>

#include "BoxColliderComponent.h"
#include "SpriteComponent.h"

MsPacmanCode::MsPacmanCode()
{
}

void MsPacmanCode::InitializeResources()
{
	InitSpawnMap();
	
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MsPacman");

//	auto pacman = std::make_shared<dae::GameObject>("PacMan");
//	pacman->AddComponent<ImageComponent>("PacMan.png");
//	pacman->AddComponent<MoveComponent>();
//	pacman->AddComponent<HealthComponent>(3.f);
//	pacman->AddComponent<PointsComponent>();
//	pacman->SetLocalPosition(250, 250);
//	scene.Add(pacman);

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

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	ParseCSVAndSpawn("level1.csv", scene);

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

	//auto& soundService = ServiceLocator::GetAudioService();

	//soundService.AddMusic("skibidi", "Sounds/ms_start.wav");
	//soundService.PlayMusic("skibidi", 100, 1);
}

void MsPacmanCode::AddWall(dae::Scene& scene, int col, int row ,int srcX, int srcY)
{
	auto wall = std::make_shared<dae::GameObject>("Wall");
	SDL_Rect srcRect{ srcX,srcY,8,8 };
	wall->SetLocalPosition((col * 8.f) * m_MapScalingFactor, (row * 8.f) * m_MapScalingFactor);
	wall->AddComponent<SpriteComponent>("WallsTransparent.png", srcRect, 8,8);
	wall->GetComponent<SpriteComponent>()->SetScale(3, 3);
	wall->AddComponent<BoxColliderComponent>(true,true,8.f,8.f/*,true*/);
	scene.Add(wall);
}

void MsPacmanCode::InitSpawnMap()
{
	for (int i = 0; i <= 8; ++i)
	{
		const int spriteOffsetX = (i * 8) + (2 * i);
		m_SpawnMap[std::to_string(i)] = [spriteOffsetX, this](dae::Scene& scene, int x, int y) {
			AddWall(scene, x, y, spriteOffsetX, 0); };
	}

	m_SpawnMap["MPM"] = [this](dae::Scene& scene, int x, int y) {
		MsPacMan msPacMan(scene);
		msPacMan.GetGameObject()->SetLocalPosition((x * 8.f) * m_MapScalingFactor, ((y * 8.f) * m_MapScalingFactor) - 10);

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

		auto go = std::make_shared<dae::GameObject>("MsPacManLives");
		go->SetLocalPosition(200, 750);
		go->AddComponent<TextComponent>("# lives: 3", font);
		go->AddComponent<HealthDisplayComponent>(msPacMan.GetGameObject());
		scene.Add(go);

		go = std::make_shared<dae::GameObject>("MsPacmanPoints");
		go->SetLocalPosition(400, 750);
		go->AddComponent<TextComponent>("Score: 0", font);
		go->AddComponent<PointDisplayComponent>(msPacMan.GetGameObject());
		scene.Add(go);
	};

	m_SpawnMap["PD"] = [this](dae::Scene& scene, int x, int y) {
			auto pacDot = std::make_shared<dae::GameObject>("Pac-Dot");
			SDL_Rect srcRect{ 0,0,8,8 };
			pacDot->SetLocalPosition((x * 8.f) * m_MapScalingFactor, ((y * 8.f) * m_MapScalingFactor) - 10);
			pacDot->AddComponent<SpriteComponent>("Pac-Dot.png", srcRect);
			pacDot->GetComponent<SpriteComponent>()->SetScale(m_MapScalingFactor, m_MapScalingFactor);
			pacDot->AddComponent<BoxColliderComponent>(true, false, glm::vec2{2 * m_MapScalingFactor,2 * m_MapScalingFactor }, 
				glm::vec2{3* m_MapScalingFactor,3 * m_MapScalingFactor }/*, true*/);

			pacDot->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<AddPointsEvent>(10.f));
			pacDot->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique <DestroyGameObjectEvent>(pacDot.get()));

			EventDispatcher::GetInstance().AddListener<DestroyGameObjectEvent>
				(pacDot.get(), [this](const DestroyGameObjectEvent& event)
					{
						event.m_GameObjDestroy->SetToDestroy();
					}
				);

			scene.Add(pacDot);
		};

	m_SpawnMap["PP"] = [this](dae::Scene& scene, int x, int y) {
		auto powerPellet = std::make_shared<dae::GameObject>("Power-Pellet");
		SDL_Rect srcRect{ 0,0,8,8 };
		powerPellet->SetLocalPosition((x * 8.f) * m_MapScalingFactor, ((y * 8.f) * m_MapScalingFactor) - 10);
		powerPellet->AddComponent<SpriteComponent>("Power-Pellet.png", srcRect);
		powerPellet->GetComponent<SpriteComponent>()->SetScale(m_MapScalingFactor, m_MapScalingFactor);
		powerPellet->AddComponent<BoxColliderComponent>(true, false, 8 * m_MapScalingFactor, 8 * m_MapScalingFactor/*, true*/);

		powerPellet->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<AddPointsEvent>(50.f));
		powerPellet->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<DestroyGameObjectEvent>(powerPellet.get()));

		EventDispatcher::GetInstance().AddListener<DestroyGameObjectEvent>
			(powerPellet.get(), [this](const DestroyGameObjectEvent& event)
				{
					event.m_GameObjDestroy->SetToDestroy();
				}
			);

		scene.Add(powerPellet);
		};
}

inline void Trim(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), str.end());
}

void MsPacmanCode::ParseCSVAndSpawn(const std::string& filepath, dae::Scene& scene)
{
	std::string string = dae::ResourceManager::GetResourcePath(filepath);
	std::ifstream file(string);
	if (!file)
	{
		std::cerr << "Failed to open CSV file: " << filepath << "\n";
		return;
	}

	std::vector<std::string> lines;

	std::string line;
	bool firstLine = true;

	while (std::getline(file, line))
	{
		// Strip BOM on first line only
		if (firstLine)
		{
			firstLine = false;
			if (line.size() >= 3 &&
				static_cast<unsigned char>(line[0]) == 0xEF &&
				static_cast<unsigned char>(line[1]) == 0xBB &&
				static_cast<unsigned char>(line[2]) == 0xBF)
			{
				line = line.substr(3);
			}
		}
		lines.push_back(line);
	}

	int row = 0;
	for (const auto& lineStr : lines)
	{
		std::stringstream ss(lineStr);
		std::string cell;
		int col = 0;

		while (std::getline(ss, cell, ';'))
		{
			Trim(cell);

			if (!cell.empty())
			{
				try
				{
					auto value = cell;
					auto it = m_SpawnMap.find(value);
					if (it != m_SpawnMap.end())
					{
						it->second(scene, col, row);
					}
				}
				catch (const std::exception& e)
				{
					std::cerr << "Failed to parse int from cell \"" << cell << "\" at (row=" << row << ", col=" << col << "): " << e.what() << "\n";
				}
			}

			++col;
		}
		++row;
	}
}
