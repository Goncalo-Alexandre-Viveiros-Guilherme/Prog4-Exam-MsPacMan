
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		//process ImGui events
		ImGui_ImplSDL2_ProcessEvent(&e);
	}	

	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	for (auto& player : m_Players)
	{
		for (auto& inputMapping : m_InputMappings)
		{
			for (auto& key : inputMapping->SDLkeys)
			{
				if (inputMapping->CurrentKeyStateIsActionState()) inputMapping->command->execute(player);
				
				if (keyState[key]) 
				{
					inputMapping->SetKeyState(true);
					break;
				}
				else inputMapping->SetKeyState(false);
			}
		}
	}

	return true;
}

void dae::InputManager::AddPlayer(GameObject* player)
{
	m_Players.emplace_back(player);
}

