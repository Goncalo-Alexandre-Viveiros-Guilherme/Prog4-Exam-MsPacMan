#pragma once
#include "Singleton.h"
#include "Commands.h"
#include <vector>
#include <memory>  
#include <SDL.h>

namespace dae
{
	enum KeyState
	{
		Pressed,
		Up,
		Down,
		Released,
		None
	};

	struct InputMapping
	{
		std::unique_ptr<Command> command; 
		std::vector<SDL_Scancode> SDLkeys;
		KeyState actionKeyState{None};
		KeyState currentKeyState{None};

		InputMapping(std::unique_ptr<Command> cmd, std::initializer_list<SDL_Scancode> keys, KeyState keystate = KeyState::Down)
			: command(std::move(cmd)), SDLkeys(keys), actionKeyState(keystate) {
		}

		void SetKeyState(bool isDown)
		{
			if (actionKeyState == None)
			{
				currentKeyState = None;
				return;
			}

			if (currentKeyState == Released) currentKeyState = Up;
			if (currentKeyState == Pressed) currentKeyState = Down;

			if (currentKeyState == None)
			{
				currentKeyState = isDown ? Down : Up;
			}

			if (currentKeyState == Down)
			{
				if (!isDown)
				{
					currentKeyState = Released;
				}
			}
			else if (currentKeyState == Up)
			{
				if (isDown) currentKeyState = Pressed; 
			}
		}

		bool CurrentKeyStateIsActionState()
		{
			return currentKeyState == actionKeyState;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		template <typename CommandType, typename... Args>
		void AddInputMapping(std::initializer_list<SDL_Scancode> keys, KeyState actionKeyState, Args&&... args)
		{
			m_InputMappings.emplace_back
			(
				std::make_unique<InputMapping>(std::make_unique<CommandType>(std::forward<Args>(args)...), keys, actionKeyState)
			);
		}

		void AddPlayer(GameObject* player);

	private:
		std::vector<std::unique_ptr<InputMapping>> m_InputMappings;
		std::vector<GameObject*> m_Players;
	};
}