#include "MsPacmanCode.h"

#include "Achievements.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
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
#include "Ghosts.h"
#include "SpriteComponent.h"
#include <GhostStates.h>

#include "MoveComponent.h"

MsPacmanCode::MsPacmanCode(GameModes gameMode): m_GameMode(gameMode), m_Scene(nullptr)
{
	dae::InputManager::GetInstance().ClearMappings();
	ServiceLocator::GetAudioService().Clear();
	ServiceLocator::GetCollisionService().Clear();
	EventDispatcher::GetInstance().Clear();
}

MsPacmanCode::~MsPacmanCode()
{
	m_SpawnMap.clear();
}


void MsPacmanCode::InitializeResources(const std::string& fileName)
{
	m_Scene = dae::SceneManager::GetInstance().CreateScene("MsPacman");

	auto obj = std::make_unique<dae::GameObject>("MsPacMan");
	m_Scene->Add(std::move<>(obj));

	InitSpawnMap();

	dae::InputManager::GetInstance().AddInputMapping<MuteCommand>({ SDL_SCANCODE_F2 }, {}, KeyPressed);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	ParseCSVAndSpawn(fileName, m_Scene);

	for (const auto& ghost : m_Ghosts)
	{
		ghost->InitializeFSM(m_Scene);
	}

	Achievements::GetInstance().NotifyAchievements();
}

void MsPacmanCode::LoadGameCode(const std::string& fileName)
{
	InitializeResources(fileName);

	auto& soundService = ServiceLocator::GetAudioService();

	soundService.AddMusic("skibidi", "Sounds/ms_start.wav");
	soundService.PlayMusic("skibidi", 100, 1);

	dae::SceneManager::GetInstance().QueueSceneChange(m_Scene);
}

void MsPacmanCode::AddWall(dae::Scene* scene, int col, int row ,int srcX, int srcY, int wallType, float rotation)
{
	auto wall = std::make_unique<dae::GameObject>("Wall");
	SDL_Rect srcRect{ srcX,srcY,8,8 };
	int dstH{ 8 };
	int dstW{ 8 };
	wall->SetLocalPosition((col * 8.f) * m_MapScalingFactor, (row * 8.f) * m_MapScalingFactor);

	wallType;
	glm::vec2 spriteSize{ 8,8 };
	wall->AddComponent<BoxColliderComponent>(true, true, 8.f * m_MapScalingFactor, 8.f * m_MapScalingFactor);

	wall->AddComponent<SpriteComponent>("WallsTransparent.png", srcRect, dstW, dstH, rotation);
	wall->GetComponent<SpriteComponent>()->SetScale(3, 3);

	scene->Add(std::move<>(wall));
}

void MsPacmanCode::InitSpawnMap()
{
	for (int i = 0; i <= 8; ++i)
	{
		const int spriteOffsetX = (i * 8) + (2 * i);
		m_SpawnMap[std::to_string(i)] = [spriteOffsetX, i,this](dae::Scene* scene, int x, int y, float rotation) {
			AddWall(scene, x, y, spriteOffsetX, 0, i, rotation); };
	}

	m_SpawnMap["MPM"] = [this](dae::Scene* scene, int x, int y, float rotation) {
		rotation;
		MsPacMan msPacMan(scene, {(x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0});

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

		if (m_GameMode == Normal)
		{
			auto& inputManager = dae::InputManager::GetInstance();

			const auto moveComponent = msPacMan.GetGameObject()->GetComponent<MoveComponent>();

			inputManager.AddInputMapping<MoveCommand>({}, { GamePad_DPadUp }, KeyDown, 160.f, DesiredDirection::Up, moveComponent);
			inputManager.AddInputMapping<MoveCommand>({}, { GamePad_DPadDown }, KeyDown, 160.f, DesiredDirection::Down, moveComponent);
			inputManager.AddInputMapping<MoveCommand>({}, { GamePad_DPadLeft }, KeyDown, 160.f, DesiredDirection::Left, moveComponent);
			inputManager.AddInputMapping<MoveCommand>({}, { GamePad_DPadRight }, KeyDown, 160.f, DesiredDirection::Right, moveComponent);
		}

		

		auto go = std::make_unique<dae::GameObject>("MsPacManLives");
		go->SetLocalPosition(200, 750);
		go->AddComponent<TextComponent>("# lives: 3", font);
		go->AddComponent<HealthDisplayComponent>(msPacMan.GetGameObject());
		scene->Add(std::move<>(go));

		go = std::make_unique<dae::GameObject>("MsPacmanPoints");
		go->SetLocalPosition(400, 750);
		go->AddComponent<TextComponent>("Score: 0", font);
		go->AddComponent<PointDisplayComponent>(msPacMan.GetGameObject());
		scene->Add(std::move<>(go));
	};

	m_SpawnMap["PD"] = [this](dae::Scene* scene, int x, int y, float rotation) {
			auto pacDot = std::make_unique<dae::GameObject>("Pac-Dot");
			SDL_Rect srcRect{ 0,0,8,8 };
			pacDot->SetLocalPosition((x * 8.f) * m_MapScalingFactor, ((y * 8.f) * m_MapScalingFactor));
			pacDot->AddComponent<SpriteComponent>("Pac-Dot.png", srcRect, rotation);
			pacDot->GetComponent<SpriteComponent>()->SetScale(m_MapScalingFactor, m_MapScalingFactor);
			pacDot->AddComponent<BoxColliderComponent>(true, false, glm::vec2{2 * m_MapScalingFactor,2 * m_MapScalingFactor },
				glm::vec2{3* m_MapScalingFactor,3 * m_MapScalingFactor }/*, true*/);

			pacDot->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<AddPointsEvent>(10.f), scene->GetGameObjectByName("MsPacMan"));
			pacDot->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique <DestroyGameObjectEvent>(pacDot.get()), scene->GetGameObjectByName("MsPacMan"));

			EventDispatcher::GetInstance().AddListener<DestroyGameObjectEvent>
				(pacDot.get(), [this](const DestroyGameObjectEvent& event)
					{
						event.m_GameObjDestroy->SetToDestroy();
					}
				);

			scene->Add(std::move<>(pacDot));
		};

	m_SpawnMap["PP"] = [this](dae::Scene* scene, int x, int y, float rotation) {
		auto powerPellet = std::make_unique<dae::GameObject>("Power-Pellet");
		SDL_Rect srcRect{ 0,0,8,8 };
		powerPellet->SetLocalPosition((x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor);
		powerPellet->AddComponent<SpriteComponent>("Power-Pellet.png", srcRect, rotation);
		powerPellet->GetComponent<SpriteComponent>()->SetScale(m_MapScalingFactor, m_MapScalingFactor);
		powerPellet->AddComponent<BoxColliderComponent>(true, false, 8 * m_MapScalingFactor, 8 * m_MapScalingFactor/*, true*/);

		powerPellet->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<AddPointsEvent>(50.f), scene->GetGameObjectByName("MsPacMan"));
		powerPellet->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<DestroyGameObjectEvent>(powerPellet.get()), scene->GetGameObjectByName("MsPacMan"));
		powerPellet->GetComponent<BoxColliderComponent>()->AddOnEnterEvent(std::make_unique<EdibleGhostsEvent>());

		EventDispatcher::GetInstance().AddListener<DestroyGameObjectEvent>
			(powerPellet.get(), [this](const DestroyGameObjectEvent& event)
				{
					event.m_GameObjDestroy->SetToDestroy();
				}
			);

		scene->Add(std::move<>(powerPellet));
		};
	
		m_SpawnMap["Blinky"] = [this](dae::Scene* scene, int x, int y, float rotation) {
			rotation;
			if (m_GameMode == Versus)
			{
				std::unique_ptr<PlayerBlinky> blinky = std::make_unique<PlayerBlinky>(scene, glm::vec3{ (x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0 });
			}
			else
			{
				std::unique_ptr<Blinky> blinky = std::make_unique<Blinky>(scene, glm::vec3{ (x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0 });

				m_Ghosts.emplace_back(std::move<>(blinky));
			}

		};

		m_SpawnMap["Inky"] = [this](dae::Scene* scene, int x, int y, float rotation) {
			rotation;
			if (m_GameMode == Versus) return;

			std::unique_ptr<Inky> inky = std::make_unique<Inky>(scene, glm::vec3{ (x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0 });

			m_Ghosts.emplace_back(std::move<>(inky));
			};

		m_SpawnMap["Pinky"] = [this](dae::Scene* scene, int x, int y, float rotation) {
			rotation;

			if (m_GameMode == Versus) return;

			std::unique_ptr<Pinky> pinky = std::make_unique<Pinky>(scene, glm::vec3{ (x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0 });

			m_Ghosts.emplace_back(std::move<>(pinky));
			};

		m_SpawnMap["Clyde"] = [this](dae::Scene* scene, int x, int y, float rotation) {
			rotation;

			if (m_GameMode == Versus) return;

			std::unique_ptr<Clyde> clyde = std::make_unique<Clyde>(scene, glm::vec3{ (x * 8.f) * m_MapScalingFactor, (y * 8.f) * m_MapScalingFactor,0 });

			m_Ghosts.emplace_back(std::move<>(clyde));
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

void MsPacmanCode::ParseCSVAndSpawn(const std::string& filepath, dae::Scene* scene)
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
					std::istringstream cellStream(cell);
					std::string type;
					float rotation = 0.0f;

					cellStream >> type;
					cellStream >> rotation;

					auto it = m_SpawnMap.find(type);
					if (it != m_SpawnMap.end())
					{
						it->second(scene, col, row, rotation);
					}
					else
					{
						std::cerr << "Unknown cell type: " << type << " at (row=" << row << ", col=" << col << ")\n";
					}
				}
				catch (const std::exception& e) 
				{
					std::cerr << "Failed to parse cell \"" << cell << "\" at (row=" << row << ", col=" << col << "): " << e.what() << "\n";
				}
			}

			++col;
		}
		++row;
	}
}
