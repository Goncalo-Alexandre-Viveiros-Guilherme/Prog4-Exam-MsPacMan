#pragma once
#include "Singleton.h"
#include "Commands.h"
#include <vector>
#include <memory>  
#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

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
		std::vector<WORD> GamepadButtons;
		KeyState actionKeyState{None};
		KeyState currentKeyState{None};
		int playerNumber; 

		InputMapping(std::unique_ptr<Command> cmd,
			std::initializer_list<SDL_Scancode> keys,
			std::initializer_list<WORD> buttons = {},
			KeyState keystate = KeyState::Down,
			int playerNum = 0)
			: command(std::move(cmd)), SDLkeys(keys), GamepadButtons(buttons),
			actionKeyState(keystate), playerNumber(playerNum) {}

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
		void AddInputMapping(std::initializer_list<SDL_Scancode> keys,
			std::initializer_list<WORD> buttons = {},
			KeyState actionKeyState = KeyState::Down,
			int playerNumber = 0,
			Args&&... args)
		{
			m_InputMappings.emplace_back(
				std::make_unique<InputMapping>(std::make_unique<CommandType>(std::forward<Args>(args)...), keys, buttons, actionKeyState, playerNumber)
			);
		}

		//Template which only takes keys and arguments as parameters for easier Input Binding
		template <typename CommandType, typename... Args>
		void AddInputMapping(std::initializer_list<SDL_Scancode> keys,
			Args&&... args)
		{
			m_InputMappings.emplace_back(
				std::make_unique<InputMapping>(std::make_unique<CommandType>(std::forward<Args>(args)...), keys)
			);
		}

		void AddPlayer(GameObject* player,int plyrNr = 0);

	private:
		std::vector<std::unique_ptr<InputMapping>> m_InputMappings;
		std::vector<GameObject*> m_Players;
		std::vector<int> m_PlayerNr;
	};
}