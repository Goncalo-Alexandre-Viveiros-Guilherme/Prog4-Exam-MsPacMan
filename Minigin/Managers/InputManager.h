#pragma once
#include "Singleton.h"
#include "Commands.h"
#include <vector>
#include <memory>  
#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

enum KeyState
{
	KeyPressed,
	KeyUp,
	KeyDown,
	KeyReleased,
	KeyNone
};

enum GamepadButtons
{
	GamePad_DPadUp = 0x0001,
	GamePad_DPadDown = 0x0002,
	GamePad_DPadLeft = 0x0004,
	GamePad_DPadRight = 0x0008,
	GamePad_Start = 0x0010,
	GamePad_Back = 0x0020,
	GamePad_LeftThumb = 0x0040,
	GamePad_RightThumb = 0x0080,
	GamePad_LeftShoulder = 0x0100,
	GamePad_RightShoulder = 0x0200,
	GamePad_A = 0x1000,
	GamePad_B = 0x2000,
	GamePad_X = 0x4000,
	GamePad_Y = 0x8000
};

namespace dae
{
	struct InputMappingImpl;
	struct InputMapping
	{
	private:
		std::unique_ptr<InputMappingImpl> m_pIMapImpl;

	public:
		InputMapping(std::unique_ptr<Command> cmd,
			std::initializer_list<SDL_Scancode> keys,
			std::initializer_list<int> buttons = {},
			KeyState keystate = KeyState::KeyDown);

		~InputMapping(); 

		void SetKeyState(bool isDown);

		std::vector<SDL_Scancode> GetSDLKeys();
		std::vector<int> GetGamepadButtons();
		void ExecuteCommand();

		bool CurrentKeyStateIsActionState();
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void ClearMappings();
		bool ProcessInput();

		template <typename CommandType, typename... Args>
		void AddInputMapping(std::initializer_list<SDL_Scancode> keys,
			std::initializer_list<int> buttons = {},
			KeyState actionKeyState = KeyState::KeyDown,
			Args&&... args)
		{
			m_InputMappings.emplace_back(
				std::make_unique<InputMapping>(std::make_unique<CommandType>(std::forward<Args>(args)...), keys, buttons, actionKeyState));
		}

	private:
		std::vector<std::unique_ptr<InputMapping>> m_InputMappings;
	};
}