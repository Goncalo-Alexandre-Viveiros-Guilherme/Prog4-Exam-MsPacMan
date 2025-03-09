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
		std::vector<int> GamepadButtons;
		KeyState actionKeyState{None};
		KeyState currentKeyState{None}; 

		InputMapping(std::unique_ptr<Command> cmd,
			std::initializer_list<SDL_Scancode> keys,
			std::initializer_list<int> buttons = {},
			KeyState keystate = KeyState::Down)
			: command(std::move(cmd)), SDLkeys(keys), GamepadButtons(buttons),
			actionKeyState(keystate){}

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
			std::initializer_list<int> buttons = {},
			KeyState actionKeyState = KeyState::Down,
			Args&&... args)
		{
			m_InputMappings.emplace_back(
				std::make_unique<InputMapping>(std::make_unique<CommandType>(std::forward<Args>(args)...), keys, buttons, actionKeyState)
			);
		}

	private:
		std::vector<std::unique_ptr<InputMapping>> m_InputMappings;
	};
}