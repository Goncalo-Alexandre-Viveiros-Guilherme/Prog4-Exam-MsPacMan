
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include <Xinput.h>

namespace dae
{
    struct InputMappingImpl
    {
    private:
        std::unique_ptr<Command> command;
        std::vector<SDL_Scancode> SDLkeys;
        std::vector<int> GamepadButtons;
        KeyState actionKeyState{ KeyNone };
        KeyState currentKeyState{ KeyNone };

    public:
        InputMappingImpl(std::unique_ptr<Command> cmd,
            std::initializer_list<SDL_Scancode> keys,
            std::initializer_list<int> buttons = {},
            KeyState keystate = KeyState::KeyDown) :
            command(std::move(cmd)), SDLkeys(keys), GamepadButtons(buttons), actionKeyState(keystate) {
        };

        void DoSetKeyState(bool isDown)
        {
            if (actionKeyState == KeyNone)
            {
                currentKeyState = KeyNone;
                return;
            }

            if (currentKeyState == KeyReleased) currentKeyState = KeyUp;
            if (currentKeyState == KeyPressed) currentKeyState = KeyDown;

            if (currentKeyState == KeyNone)
            {
                currentKeyState = isDown ? KeyDown : KeyUp;
            }

            if (currentKeyState == KeyDown)
            {
                if (!isDown)
                {
                    currentKeyState = KeyReleased;
                }
            }
            else if (currentKeyState == KeyUp)
            {
                if (isDown) currentKeyState = KeyPressed;
            }
        }

        std::vector<SDL_Scancode> DoGetSDLKeys() { return SDLkeys; }

        std::vector<int> DoGetGamepadButtons() { return GamepadButtons; }

        void DoExecuteCommand() { if(command != nullptr) command->Execute(); }

        bool DoCurrentKeyStateIsActionState()
        {
            return currentKeyState == actionKeyState;
        }
    };
}
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

	// Get controller state
	XINPUT_STATE controllerState{};
	bool controllerConnected = (XInputGetState(0, &controllerState) == ERROR_SUCCESS); // Assume controller 0

    for (auto& inputMapping : m_InputMappings)
    {
        bool actionTriggered = false;
        // checks for keyboard
        for (auto& key : inputMapping->GetSDLKeys())
        {
            if (keyState[key])
            {
                inputMapping->SetKeyState(true);
                actionTriggered = true;
                break;
            }
        }
        // check controller
        if (controllerConnected)
        {
            for (auto& button : inputMapping->GetGamepadButtons())
            {
                if (controllerState.Gamepad.wButtons & button)
                {
                    inputMapping->SetKeyState(true);
                    actionTriggered = true;
                    break;
                }
            }
        }

        // Execute if the key state matches the action state
        if (inputMapping->CurrentKeyStateIsActionState())
        {
            inputMapping->ExecuteCommand();
        }

        // else reset it
        if (!actionTriggered)
        {
            inputMapping->SetKeyState(false);
        }
    }


	return true;
}

dae::InputMapping::InputMapping(std::unique_ptr<Command> cmd, std::initializer_list<SDL_Scancode> keys, std::initializer_list<int> buttons, KeyState keystate)
{
    m_pIMapImpl = new InputMappingImpl(std::move(cmd), keys, buttons, keystate);
}

dae::InputMapping::~InputMapping()
{
    delete m_pIMapImpl;
}

void dae::InputMapping::SetKeyState(bool isDown)
{
   m_pIMapImpl->DoSetKeyState(isDown);
}

std::vector<SDL_Scancode> dae::InputMapping::GetSDLKeys()
{
    return m_pIMapImpl->DoGetSDLKeys();
}

std::vector<int> dae::InputMapping::GetGamepadButtons()
{
    return m_pIMapImpl->DoGetGamepadButtons();
}

void dae::InputMapping::ExecuteCommand()
{
    m_pIMapImpl->DoExecuteCommand();
}

bool dae::InputMapping::CurrentKeyStateIsActionState()
{
    return m_pIMapImpl->DoCurrentKeyStateIsActionState();
}
